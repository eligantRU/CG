#pragma once

#include "MeshP3NT2.h"
#include "libchapter3.h"
#include "IRenderer3D.h"

class CIdentitySphere
{
public:
	CIdentitySphere(unsigned slices, unsigned stacks);

	void Draw(IRenderer3D & renderer) const;

private:
	CMeshP3NT2 m_mesh;
};
