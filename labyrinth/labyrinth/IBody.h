#pragma once

#include "stdafx.h"

class IBody
{
public:
    virtual ~IBody() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() const = 0;
};

using IBodyUniquePtr = std::unique_ptr<IBody>;
