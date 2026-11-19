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
#include "core/types/MeshMaterial.h"
#include "core/types/Vec3.h"
#include <memory>
namespace us {

class IMeshProductOutput : public us::IProductOutput
{
public:
    class Geometry
    {
    public:
        enum class Type { Position, Normal, UV, Color };
        using Buffer = std::vector<float>;
        int _size;
        std::unordered_map<Type, Buffer> _data;
    };

    class Update
    {
    public:
        // the ids of the geometry and material this output shows, 0 if none (see Listener)
        std::uint64_t _geometry = 0;
        std::uint64_t _material = 0;
        std::vector<Transformation> _instances;
        bool _visible;
        std::string _displayName;
        std::string _description;
        std::string _externalID;
    };

    /**
     * Geometries and materials are sent separately from the updates, identified
     * by an id that the updates refer to. Passes of a product that compute the
     * same geometry or material (see PassesGroups) refer to the same id.
     *
     * - Added: the id is in use from now on. It comes before any update that
     *   refers to it. Its content may come later, e.g. when the pass that
     *   computes it executes after the one that refers to it; until then an
     *   output that refers to it shows nothing.
     * - Changed: the content of the id. An id keeps its content until it
     *   changes again, which concerns every output that refers to it. It
     *   comes once per change, through the output that computed it.
     * - Removed: the id isn't in use anymore. Outputs that referred to it
     *   refer to another id by their next update, which may come after it.
     *
     * Every output of the node reports the Added and Removed of its ids, also
     * outputs that don't refer to them. A listener of several outputs handles
     * only the first of each (see ResourceReferences), as Monitor does. The
     * engine doesn't keep the content after it has sent it.
     */
    class Listener
    {
    public:
        virtual void onUpdate(IMeshProductOutput *aOutput, const Update &aUpdate);

        virtual void onGeometryAdded(IMeshProductOutput *aOutput, std::uint64_t aID);
        virtual void onGeometryChanged(IMeshProductOutput *aOutput,
                                       std::uint64_t aID,
                                       const std::shared_ptr<const Geometry> &aGeometry);
        virtual void onGeometryRemoved(IMeshProductOutput *aOutput, std::uint64_t aID);

        virtual void onMaterialAdded(IMeshProductOutput *aOutput, std::uint64_t aID);
        virtual void onMaterialChanged(IMeshProductOutput *aOutput,
                                       std::uint64_t aID,
                                       const std::shared_ptr<const MeshMaterial> &aMaterial);
        virtual void onMaterialRemoved(IMeshProductOutput *aOutput, std::uint64_t aID);
    };

    virtual ~IMeshProductOutput();

    /**
     * Adds a Listener
     * @note This IMeshProductOutput does not take ownership of the given
     *       listener. Its lifetime should exceed the moment
     *       the listener is removed. It is not needed to remove
     *       the listener before the end of this IMeshProductOutput's lifetime.
     */
    virtual void addListener(Listener *aListener) = 0;
    /**
     * Removes the given Listener
     */
    virtual void removeListener(Listener *aListener) = 0;
};

} // namespace us
