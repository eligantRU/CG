#pragma once

#include "stdafx.h"
#include "Rectangle.h"

namespace
{
	void FillSquare(float xCenter, float yCenter, float dx, float dy, float angle)
	{
		angle *= float(180 / M_PI);

		glPushMatrix();

		glTranslatef(xCenter, yCenter, 0);
		glRotatef(angle, 0, 0, 1);

		glBegin(GL_QUADS);
		glVertex2f(-dx, -dy);
		glVertex2f(+dx, -dy);
		glVertex2f(+dx, +dy);
		glVertex2f(-dx, +dy);
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
