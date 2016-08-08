#pragma once

#include "stdafx.h"
#include "Rectangle.h"
#include "consts.h"

namespace
{
	void FillSquare(float xCenter, float yCenter, float dx, float dy, float angle)
	{
		angle *= float(180 / M_PI);

		glPushMatrix();

		glTranslatef(xCenter, yCenter, 0);
		glRotatef(angle, 0, 0, 1);

		glBegin(GL_QUADS);
		glColor3f(BARRIER_COLOUR.x, BARRIER_COLOUR.y, BARRIER_COLOUR.z);
		glVertex2f(-dx, -dy);
		glVertex2f(+dx, -dy);
		glVertex2f(+dx, +dy);
		glVertex2f(-dx, +dy);
		glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);
		glEnd();

		glPopMatrix();
	}
}

void CRectangle::Draw() const
{
	auto position = GetPosition();
	auto size = GetSize();
	FillSquare(position.x, position.y, size.x, size.y, GetRotation());
}
