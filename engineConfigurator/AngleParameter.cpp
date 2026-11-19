/*
 * Copyright (c) 2024-2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */

#include "AngleParameter.h"

#include "core/IDataDocument.h"
#include "core/IProductConfiguration.h"
#include "core/NodeInputT.h"
#include "core/NodeOutputT.h"
#include "core/categories/NodeTypes.h"
#include "core/parameters/INumberParameter.h"

using namespace us;

///The INumberParameter implementation registered to
///the product configuration, per pass
class AngleParameter::AngleRegisteredParameter : public INumberParameter
{
public:
    AngleRegisteredParameter(IProductConfiguration *aConfiguration,
                             AngleParameter *aP,
                             const std::string &aID,
                             const Pass &aPass)
        : _parent(aP)
        , _productConfiguration(aConfiguration)
        , _id(aID)
        , _value(aP->_defaultValue.fallbackValue().get<float>())
        , _default(_value)
        , _pass(aPass)
        , _visible(true)

    {
        //The parameter is registereed to the product
        _productConfiguration->addParameter(this);
    }

    virtual ~AngleRegisteredParameter()
    {
        //The parameter is unregistered from the product
        _productConfiguration->removeParameter(this);
    }

    // returns an id with which the parameter is uniquely defined
    std::string id() const override { return _id; }
    // the name of this parameter in the UI.
    // For a production ready implementation please
    // make sure to include a connectable displayName
    // input to AngleParameter so that every instance
    // of this class can have a meaningful display name.
    // For the sake of simplicity this demo returns a
    // constant value.
    std::string displayName() const override { return "Angle"; }

    //returns the current value of the parameter
    float value() const override {
        return _value;
    }
    //updates the value. Invalidates the output.
    //Invalidating the output starts a cascade
    //of invalidations through the graph:
    //INodeInputs listen for state changes
    //in their connected outputs and update their
    //own states. ANode implementations listen for
    //INodeInput state changes and invalidate
    //their outputs accordingly.
    bool setValue(float aValue) override
    {
        if (aValue < minimumValue()) {
            aValue = minimumValue();
        }
        if (aValue > maximumValue()) {
            aValue = maximumValue();
        }
        if (std::abs(aValue - _value) < 1e-4f) {
            return false;
        }
        _value = aValue;
        _parent->_output.invalidate(_pass);
        for(auto & l : _listeners){
            l->onValueChanged(this,_value);
        }
        return true;
    }

    void accept(IParameterVisitor *aVisitor) override
    {
        aVisitor->visit(this);
    }

    float minimumValue() const override { return 0.0f; }

    float maximumValue() const override { return 720.0f; }

    void addListener(INumberParameter::Listener *aListener) override
    {
        _listeners.insert(aListener);
    }
    void removeListener(INumberParameter::Listener *aListener) override
    {
        _listeners.erase(aListener);
    }

    bool visible() const override { return _visible; }

    bool editable() const override { return true; }

    float defaultValue() const override { return _default; }

    Presentation presentation() const override { return Presentation::Slider; }

    std::string externalID() const override { return ""; }

    std::string unit() const override { return "degrees"; }

    std::string description() const override { return "Angle (in degrees)"; }

    void setVisible(bool aVisible)
    {
        if (aVisible == _visible) {
            return;
        }
        _visible = aVisible;
        for (auto &l : _listeners) {
            l->onVisibleChanged(this, _visible);
        }
    }
    //updates the default value of this parameter. Updates
    //the current value of the parameter accordingly.
    //The cautious reader probably has spotted an
    //inconsistency here: setValue invalidates the output,
    //while setDefault is called while executing the node.
    //Although the programming guide specifically claims
    //never to invalidate outputs while executing. Invalidating
    //an output while executing confuses graph traversal and
    //should be avoided at all costs.
    //The cautious reader is right. Why it works in this case?
    //Because when the default value input is invalidated ( while
    //not executing), it invalidates all outputs. Invalidating
    //the output again won't make a difference, because the output
    //has already been invalidated.
    void setDefault(float aDefault)
    {
        aDefault = std::min(std::max(aDefault, minimumValue()), maximumValue());
        if (std::abs(aDefault - _default) < 1e-4f) {
            return;
        }
        _default = aDefault;
        setValue(_default);
        for (auto &l : _listeners) {
            l->onDefaultValueChanged(this, _default);
        }
    }

    float _value;

    float _default;

    bool _visible;

    std::string _id;

    Pass _pass;

    AngleParameter *_parent;

    IProductConfiguration * _productConfiguration;

    std::unordered_set<INumberParameter::Listener *> _listeners;
};

AngleParameter::AngleParameter(Definition *aDefinition,
                               IProductConfiguration *aProductConfiguration,
                               const std::string &aID,
                               const ExtensionProviders &aExtensionProviders,
                               const NodePosition &aPosition)
    : ANode(aDefinition, aProductConfiguration, aID, aExtensionProviders, aPosition)
    , _output(this, "value", "the float parameter value")
    , _visible(this, "visible", "Whether this parameter should be visible")
    , _defaultValue(this, "default", "Default value of this parameter")
{
    //always set fallback values for all inputs
    _defaultValue.setFallbackValue(float(0.0f));
    _visible.setFallbackValue(bool(true));
    //register all in- and outputs. Otherwise
    //ANode is not aware of them.
    registerInput(&_defaultValue);
    registerOutput(&_output);
    //the extra 'false' argument signals
    //tells ANode not to invalidate
    //its outputs when this input
    //gets invalidated.
    //that is intended behavior for a
    //property that does not affect the graph
    //output such as visible. And because
    //AngleParameter registers itself as
    //Properties endpoint, its value
    //is updated nevertheless.
    registerInput(&_visible, false);
    //register parameters for all current passes
    for (auto &p : configuration()->passes()) {
        onBeginAddPass(p);
    }
    //register this node as a Properties endpoint. This
    //means that while executing the Properties target,
    //the traversal starts from this node ( and other nodes
    //registered as Properties endpoint). This guarantees
    //that this node is executed at all times.
    configuration()->addEndpoint(this, {Target::Properties});
}

AngleParameter::~AngleParameter()
{
    //unregisters this node as an endpoint
    configuration()->removeEndpoint(this);
    //unregisters all in- and outputs
    unregisterOutput(&_output);
    unregisterInput(&_defaultValue);
    unregisterInput(&_visible);
}

//ANodeDefinition takes the name of the node definition as it appears in the
//node definitions list, as well as a set of categories under which you
//can find it. Feel free to add your own categories.
AngleParameter::Definition::Definition()
    : ANodeDefinition("Angle parameter", {NodeTypes::parameterType()})
{}

std::string AngleParameter::Definition::type() const
{
    return "AngleParameter";
}

std::string AngleParameter::Definition::description() const
{
    return "Parameter returning a angle in degrees";
}

//Executes this node. Notice that two targets are handled: Default and Properties.
//The Properties target is passed by the engine when graph traversal starts
//with this node while executing the Properties pass. In all other cases ( even when
//re-visiting the node while executing the Properties pass ) the
//Default target is passed to this method.
//Note that _defaultValue is evaluated during the Properties pass. This
//to make sure default values are updated accordingly, even when nothing
//is connected to this node's output.
void AngleParameter::executeImpl(Target aTarget, const Pass &aPass)
{
    if (!requiredDependencies(aTarget, aPass).empty()) {
        return;
    }
    if (aTarget == Target::Default) {
        auto &d = _d.at(aPass);
        _output.setValue(aPass, Degrees(d->_value));
    } else if (aTarget == Target::Properties) {
        auto &d = _d.at(aPass);
        if (_visible.state(aPass) == INodeInput::State::Invalid) {
            d->setVisible(_visible.acceptValue(aPass));
        }
        if (_defaultValue.state(aPass) == INodeInput::State::Invalid) {
            d->setDefault(_defaultValue.acceptValue(aPass));
        }
    }
}

INode *AngleParameter::Definition::create(IProductConfiguration *aConfiguration,
                                          const std::string &aID,
                                          const ExtensionProviders &aExtensionProviders,
                                          const NodePosition &aPosition)
{
    return new AngleParameter(this, aConfiguration, aID, aExtensionProviders, aPosition);
}

std::vector<us::INodeOutput *> AngleParameter::requiredDependencies(Target aTarget,
                                                                    const Pass &aPass)
{
    if (aTarget == Target::Properties) {
        std::vector<INodeOutput *> result;
        for (auto i : std::vector<INodeInput *>{&_visible,
                                                &_defaultValue}) {
            //Note here the condition that the input needs to be
            //invalidated. If not invalidated the cached value
            //accepted earlier is enough, even if the connected
            //output has been released.
            if (i->state(aPass) == INodeInput::State::Invalid && i->connection()
                && i->connection()->state(aPass) != INodeOutput::State::Available) {
                result.push_back(i->connection());
            }
        }
        return result;
    }
    //no regular dependencies
    return {};
}

//This method saves the state of this node, so that it can
//be restored later. Typically the state can be restored
//by logging the user provided inputs, for all passes.
//That's why 'value' is saved in this case. However note
//that defaultValue can change the current value. That means
//that running the graph after restoring a configuration
//can overwrite the value to a different value again.
//That's why also the default value is saved.
void AngleParameter::save(IDataDocument &aConfiguration)
{
    if (aConfiguration.create(id())) {
        for (auto &[pass, d] : _d) {
            if (aConfiguration.create(pass)) {
                aConfiguration.insert("value", std::to_string(d->_value));
                aConfiguration.insert("defaultValue", std::to_string(d->_default));
                aConfiguration.pop();
            }
        }
        aConfiguration.pop();
    }
}
//Restores the state of this node based on the given
//configuration.
void AngleParameter::load(us::IDataDocument &aConfiguration)
{
    if (aConfiguration.push(id())) {
        for (auto &[pass, d] : _d) {
            if (aConfiguration.push(pass)) {
                try {
                    // the default first, as setting it resets the value
                    d->setDefault(std::stof(aConfiguration.value("defaultValue")));
                    d->setValue(std::stof(aConfiguration.value("value")));
                } catch (...) {
                }
                aConfiguration.pop();
            }
        }

        aConfiguration.pop();
    }
}

//Adds and registers a parameter when a pass is added.
void AngleParameter::onBeginAddPass(const Pass &aPass)
{
    _d[aPass] = std::make_unique<AngleRegisteredParameter>(configuration(),
                                                           this,
                                                           aPass + "/" + id(),
                                                           aPass);
}

//Unregisters and removes a parameterwhen a pass is removed.
void AngleParameter::onBeginRemovePass(const Pass &aPass)
{
    _d.erase(aPass);
}

PassesGroups AngleParameter::partitionGroups() const
{
    //a parameter can assume any value per pass. That
    //means the value for every pass is unique. That is
    //why we return an empty list here.
    return {};
}
