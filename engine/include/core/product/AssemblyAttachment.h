/*
 * Copyright (c) 2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */
#pragma once

#include "core/types/Selection.h"
#include "core/types/Vec3.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace us {

class AssemblyAttachment
{
public:
    Selection _accepted = Selection::ALL();
    std::vector<std::string> _tags;
    Vec3 _position;
    Vec3 _align;
    Vec3 _outwards;
};

using AssemblyAttachmentPtr = std::shared_ptr<AssemblyAttachment>;

/**
 * Whether aExisting, an attachment of an instance that is already placed, accepts the
 * tags of aNew. The selection of aNew plays no part.
 */
bool accepts(const AssemblyAttachment &aExisting, const AssemblyAttachment &aNew);

/**
 * The attachment with its position and directions transformed by aTransformation
 */
AssemblyAttachment transformed(const AssemblyAttachment &aAttachment,
                               const Transformation &aTransformation);

/**
 * The transformation that moves aOwn onto aTarget: their positions coincide,
 * their align vectors coincide and their outwards vectors are opposite.
 * Empty when either attachment has parallel align and outwards vectors.
 */
std::optional<Transformation> attachTransformation(const AssemblyAttachment &aTarget,
                                                   const AssemblyAttachment &aOwn);

/**
 * Whether the attachments coincide as if aLater was attached to aEarlier, where
 * aEarlier belongs to the instance that was placed first
 */
bool connected(const AssemblyAttachment &aEarlier, const AssemblyAttachment &aLater);

/**
 * Whether both attachments are the same: position, directions, tags and acceptance
 */
bool equivalent(const AssemblyAttachment &aFirst, const AssemblyAttachment &aSecond);

/**
 * Whether aPoint lies inside aBox, excluding a thin layer at its boundary
 */
bool strictlyInside(const Eigen::AlignedBox3d &aBox, const Vec3 &aPoint);

} // namespace us
