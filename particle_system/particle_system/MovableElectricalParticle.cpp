#include "stdafx.h"
#include "MovableElectricalParticle.h"

void CMovableElectricalParticle::Draw() const
{
	glm::vec3 offset = { m_position.x, m_position.y, 0.f };
	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));
	CElectricalParticle::Draw();
	glPopMatrix();
}

bool CMovableElectricalParticle::HitTest(const glm::vec2 & point) const
{
	return CElectricalParticle::HitTest(point - GetPosition());
}

void CMovableElectricalParticle::SetPosition(const glm::vec2 & position)
{
	CElectricalParticle::SetPosition(position);
	m_position = position;
}

const glm::vec2 & CMovableElectricalParticle::GetPosition() const
{
	return m_position;
}

void CMovableElectricalParticle::SetAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration = acceleration;
}

const glm::vec2 & CMovableElectricalParticle::GetAcceleration() const
{
	return m_acceleration;
}
