#include "stdafx.h"

#include "Blocks.h"

namespace
{

}

CBarrierBlock::CBarrierBlock(const glm::vec3 & center, const float size)
	:m_cube(center, size)
	,m_position(glm::vec3(center.x - size, center.y - size, center.z - size), glm::vec3(center.x + size, center.y + size, center.z + size))
{

}

void CBarrierBlock::Update(const float dt)
{
	m_cube.Update(dt);
}

void CBarrierBlock::Draw(IRenderer3D & renderer) const
{
	m_cube.Draw(renderer);
}
