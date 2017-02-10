#pragma once

#include <cstdlib>

class IRenderer3D
{
public:
	virtual ~IRenderer3D() = default;

	virtual void SetTexCoord2DOffset(size_t offset, size_t stride) = 0;
	virtual void SetPosition3DOffset(size_t offset, size_t stride) = 0;
	virtual void SetNormalOffset(size_t offset, size_t stride) = 0;
};
