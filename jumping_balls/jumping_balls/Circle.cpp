#pragma once

#include "stdafx.h"
#include "Circle.h"
#include "consts.h"

namespace
{
void FillEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
{
	const float step = float(2 * M_PI) / pointCount;

	glPushMatrix();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(BALL_COLOUR.x, BALL_COLOUR.y, BALL_COLOUR.z);
	glVertex2f(xCenter, yCenter);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(xCenter + dx, yCenter + dy);
	}
	glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);
	glEnd();

	glPopMatrix();
}
}

void CCircle::Draw() const
{
	auto position = GetPosition();
	auto radius = GetRadius();
	FillEllipse(position.x, position.y, radius, radius);
}

void CCircle::SetRadius(float radius)
{
	m_radius = radius;
}

float CCircle::GetRadius() const
{
	return m_radius;
}
