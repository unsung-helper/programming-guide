/*
 * Copyright (c) 2024 Jucon BV
 * All rights reserved.
 *
 * This file is part of dsign. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#include "Twist.h"
#include "core/categories/NodeTypes.h"
#include "core/types/Bounds.h"
#include "Degrees.h"
#include "Radians.h"

namespace us {

Twist::Twist(Definition *aDefinition,
             IProductConfiguration *aProduct,
             const std::string &aID,
             const ExtensionProviders &aExtensionProviders,
             NodePosition aPosition)
    : ANode(aDefinition, aProduct, aID, aExtensionProviders, aPosition)
    , _mesh(this, "mesh", "The input mesh")
    //Extra boolean argument to make the mode input unconnectable
    , _mode(this, "mode", "The mode, either degrees or radians", false)
    , _result(this, "result", "The twisted mesh")
{
    //always set fallback values for all your inputs!
    _mesh.setFallbackValue(MeshPtr(nullptr));
    //Some inputs can only have some predefined
    //values. Add these values with addOption.
    //In the Node details panel these options
    //show up in a dropdown.
    _mode.addOption(RADIANS);
    _mode.addOption(DEGREES);
    _mode.setFallbackValue(RADIANS);
    //Register in- and outputs so that
    //ANode is aware of their existence
    registerInput(&_mesh);
    registerInput(&_mode);
    registerOutput(&_result);
    //Trigger onFallbackValueChanged
    //to initialize _angle.
    onFallbackValueChanged(&_mode);
    //Register this node for subsequent
    //mode fallback value changes
    _mode.addListener(this);
}

Twist::~Twist()
{
    //remove listener
    _mode.removeListener(this);
    //make sure to unregister all in-
    //and outputs before the ANode
    //destructor runs.
    if (_angle) {
        unregisterInput(_angle.get());
        _angle.reset();
    }
    unregisterInput(&_mode);
    unregisterInput(&_mesh);
    unregisterOutput(&_result);
}

std::vector<INodeOutput *> Twist::requiredDependencies(Target aTarget, const Pass &aPass)
{
    //Twist has not registered itself as endpoint for any target. You can safely
    //assume aTarget will always be Target::Default.

    //retrieve all dependencies
    std::vector<INodeOutput *> result = getDependencies();
    //this node caches no input values. So at every execution we need
    //to make sure that the input value is there, even if if was not
    //invalidated. That is the default implementation of ANode.
    result.erase(std::remove_if(result.begin(),
                                result.end(),
                                [&aPass](const INodeOutput *o) {
                                    return o->state(aPass) == INodeOutput::State::Available;
                                }),
                 std::end(result));
    return result;
}

//ANodeDefinition takes the name of the node definition as it appears in the
//node definitions list, as well as a set of categories under which you
//can find it. Feel free to add your own categories.
Twist::Definition::Definition()
    : ANodeDefinition("Mesh Twist", {NodeTypes::modifierType()})
{}

std::string us::Twist::Definition::type() const
{
    return "Twist";
}

std::string us::Twist::Definition::description() const
{
    return "Twists the input mesh along the Z-axis for a given angle. The angle can be in radians "
           "or in degrees";
}

void us::Twist::executeImpl(us::Target aTarget, const Pass &aPass)
{
    //every connectable input needs to be read and accepted
    auto mesh = _mesh.acceptValue(aPass);
    Any anyAngle = _angle->value(aPass);
    _angle->accept(aPass);

    if (mesh) {
        //retrieve the angle in radians
        double angle = 0.0;
        if (_mode.fallbackValue() == DEGREES) {
            angle = anyAngle.get<Degrees>();
            angle *= M_PI / 180.0;
        } else if (_mode.fallbackValue() == RADIANS) {
            angle = anyAngle.get<Radians>();
        }

        //compute the bounding box of the mesh by iterating all vertices
        Bounds bounds;
        for (auto vit = mesh->vertices_sbegin(); vit != mesh->vertices_end(); ++vit) {
            bounds.add(mesh->point(*vit));
        }

        const double zMin = bounds.min().z();
        const double zMax = bounds.max().z();

        if (bounds.isValid() && (zMax - zMin) > 1e-6) {
            //recenter around Z-axis
            Vec3 displacement = 0.5 * (bounds.min() + bounds.max());
            displacement.z() = 0.0;
            for (auto vit = mesh->vertices_sbegin(); vit != mesh->vertices_end(); ++vit) {
                mesh->set_point(*vit, mesh->point(*vit) - displacement);
            }
            //twist
            for (auto vit = mesh->vertices_sbegin(); vit != mesh->vertices_end(); ++vit) {
                const double a = angle * (zMax - mesh->point(*vit).z()) / (zMax - zMin);
                mesh->set_point(*vit,
                                Eigen::AngleAxisd(a, Eigen::Vector3d::UnitZ()) * mesh->point(*vit));
            }
            //put back
            for (auto vit = mesh->vertices_sbegin(); vit != mesh->vertices_end(); ++vit) {
                mesh->set_point(*vit, mesh->point(*vit) + displacement);
            }
        }
    }
    //update result
    _result.setValue(aPass, mesh);
}

INode *Twist::Definition::create(IProductConfiguration *aConfiguration,
                                 const std::string &aID,
                                 const ExtensionProviders &aExtensionProviders,
                                 const NodePosition &aPosition)
{
    return new Twist(this, aConfiguration, aID, aExtensionProviders, aPosition);
}

void us::Twist::onFallbackValueChanged(INodeInput *aInput)
{
    if (aInput != &_mode) {
        return;
    }
    //clean up previous input if it exists
    if (_angle) {
        _angle->disconnect();
        unregisterInput(_angle.get());
        _angle.reset();
    }
    //accepts new fallback value
    auto mode = _mode.acceptFallbackValue();
    //Create new input, and set fallback and register
    if (mode == RADIANS) {
        _angle = std::make_unique<NodeInputT<Radians>>(this, "angle", "The twist angle in radians");
        _angle->setFallbackValue(Radians(0.0));
        registerInput(_angle.get());
    } else if (mode == DEGREES) {
        _angle = std::make_unique<NodeInputT<Degrees>>(this, "angle", "The twist angle in degrees");
        _angle->setFallbackValue(Degrees(0.0));
        registerInput(_angle.get());
    }
}

} // namespace ds
