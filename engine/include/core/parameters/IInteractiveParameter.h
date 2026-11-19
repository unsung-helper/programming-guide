// /*
//  * Copyright (c) 2024-2026 Jucon BV
//  * All rights reserved.
//  *
//  * This file is part of unsung. Unauthorized copying, modification,
//  * distribution, or use of this file is strictly prohibited without prior
//  * written consent from Jucon BV.
//  *
//  * For inquiries regarding the use of this software, please contact: info@juconbv.be
//  */
// #pragma once

// #include "IProductParameter.h"
// #include "core/types/Buffer.h"
// #include <string>
// #include <unordered_set>

// namespace us {

// class IInteractiveDisplay;

// class IInteractiveParameter : public IProductParameter
// {
// public:
//     class Listener
//     {
//     public:
//         virtual void onDisplayNameChanged(IInteractiveParameter *aParameter,
//                                           const std::string &aName)
//             = 0;
//         virtual void onVisibleChanged(IInteractiveParameter *aParameter, bool aVisible) = 0;
//         virtual void onEditableChanged(IInteractiveParameter *aParameter, bool aEditable) = 0;
//         virtual void onExternalIDChanged(IInteractiveParameter *aParameter, std::string aExternalID)
//             = 0;
//         virtual void onDescriptionChanged(IInteractiveParameter *aParameter,
//                                           std::string aDescription)
//             = 0;

//         virtual void onActiveChanged(IInteractiveParameter *aParameter, bool aActive) = 0;

//         virtual void onActionsChanged(IInteractiveParameter *aParameter) = 0;

//         virtual void onActionExecuted(IInteractiveParameter *aParameter, std::string aAction) = 0;
//     };

//     virtual ~IInteractiveParameter();

//     virtual void addListener(Listener *aListener) = 0;

//     virtual void removeListener(Listener *aListener) = 0;

//     virtual bool makeActive(IInteractiveDisplay *aDisplay) = 0;

//     virtual void deactivate() = 0;

//     virtual bool active() const = 0;

//     virtual std::vector<std::string> actions() const = 0;

//     virtual void execute(const std::string &aAction) = 0;

//     virtual Buffer value() const = 0;

//     virtual void setValue(const Buffer &aBuffer) = 0;

// };

// } // namespace us
