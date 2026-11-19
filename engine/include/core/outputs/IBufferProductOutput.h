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
#pragma once

#include "IProductOutput.h"
#include "core/types/Buffer.h"
#include <memory>

namespace us {

class IBufferProductOutput : public us::IProductOutput
{
public:
    class Update
    {
    public:
        std::shared_ptr<Buffer> _buffer;
        std::string _displayName;
        std::string _format;
        std::string _description;
        std::string _externalID;
        /**
         * Returns the file name to save the buffer under: the display
         * name with the format as extension, unless it already has it.
         */
        std::string fileName() const;
    };

    /**
     * Base class for an IBufferProductOutput Listener
     */
    class Listener
    {
    public:
        virtual void onUpdate(IBufferProductOutput *aOutput, const Update &aUpdate);
    };

    virtual ~IBufferProductOutput();
    /**
     * Returns the format (file extension) in which the buffer is encoded
     */
    virtual std::string format() const = 0;

    /**
     * Adds a Listener
     * @note This IBufferProductOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this IBufferProductOutput's lifetime.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the given Listener
     */
    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
