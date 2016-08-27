#include "stdafx.h"

#include "Blocks.h"

namespace
{



}

CBlock::CBlock() = default;

CBlock::~CBlock() = default;

void CBlock::Update(float deltaTime)
{
	(void)deltaTime;
}

void CBlock::SetPosition(const glm::vec3 & position)
{
	m_position = position;
}

glm::vec3 CBlock::GetPosition() const
{
	return m_position;
}

void CBlock::Draw() const
{
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z); // TODO: do not use glTranslatef()
	m_cube.Draw();
	glPopMatrix();
}

CBarrierBlock::CBarrierBlock() = default;

CBarrierBlock::~CBarrierBlock() = default;

void CBarrierBlock::Draw() const
{
	CBlock::Draw();
}

CFreeBlock::CFreeBlock() = default;

CFreeBlock::~CFreeBlock() = default;

void CFreeBlock::Draw() const
{

}
