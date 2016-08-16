#include "stdafx.h"
#include "ElectricalParticle.h"
#include "consts.h"

namespace
{

void FillEllipse(float xCenter, float yCenter, float rx, float ry, glm::vec3 color, int pointCount = 360)
{
	(void)xCenter;
	(void)yCenter;
	const float step = float(2 * M_PI) / pointCount;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color.x, color.y, color.z);
	glVertex2f(0, 0);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float fixedAngle = (fabsf(angle - float(2 * M_PI)) < 1e-4f) ? 0 : angle;
		const float x = rx * cosf(fixedAngle);
		const float y = ry * sinf(fixedAngle);
		glVertex2f(x, y);
	}
	glEnd();
}
}

CElectricalParticle::~CElectricalParticle()
{
	DeleteList();
}

void CElectricalParticle::SetElectricalCharge(float charge)
{
	m_electricalCharge = charge;
}

float CElectricalParticle::GetElectricalCharge()
{
	return m_electricalCharge;
}

void CElectricalParticle::SetPosition(const glm::vec2 & position)
{
	m_position = position;
}

const glm::vec2 & CElectricalParticle::GetPosition() const
{
	return m_position;
}

float CElectricalParticle::GetRadius() const
{
	return PARTICLE_RADUIS;
}

void CElectricalParticle::Draw() const
{
	if (!m_displayList)
	{
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);
		Redraw();
		glEndList();
	}

	glCallList(m_displayList);
}

void CElectricalParticle::DeleteList()
{
	if (m_displayList)
	{
		glDeleteLists(m_displayList, 1);
		m_displayList = 0;
	}
}

void CElectricalParticle::Redraw() const
{
	FillEllipse(m_position.x, m_position.y, PARTICLE_RADUIS, PARTICLE_RADUIS, GetColor());
}

bool CElectricalParticle::HitTest(const glm::vec2 & point) const
{
	const float angle = std::atan2(point.y, point.x);
	const float radius = PARTICLE_RADUIS;

	return (glm::length(point) < radius);
}

void CElectricalParticle::SetColor(const glm::vec3 & ñolor)
{
	m_color = ñolor;
}

glm::vec3 CElectricalParticle::GetColor() const
{
	return m_color;
}
