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

namespace us {

class INumberProductOutput;
class IMeshProductOutput;
class IPolylineProductOutput;
class IPointsProductOutput;
class IStringProductOutput;
class ISceneProductOutput;
class IImageProductOutput;
class IBufferProductOutput;

class IProductOutputVisitor
{
public:
    virtual ~IProductOutputVisitor();

    virtual void visit(INumberProductOutput *aOutput) = 0;

    virtual void visit(IMeshProductOutput *aOutput) = 0;

    virtual void visit(IPolylineProductOutput *aOutput) = 0;

    virtual void visit(IPointsProductOutput *aOutput) = 0;

    virtual void visit(IStringProductOutput *aOutput) = 0;

    virtual void visit(ISceneProductOutput *aOutput) = 0;

    virtual void visit(IImageProductOutput *aOutput) = 0;

    virtual void visit(IBufferProductOutput *aOutput) = 0;
};

} // namespace us
