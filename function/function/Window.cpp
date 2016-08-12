#include "stdafx.h"
#include "Window.h"
#include "consts.h"

namespace
{
const glm::vec2 UNIT_INTERVAL = { M_PI, 1.f };
const glm::vec2 SCALE = { 1.f / 8.f, 1.f / 2.f };
const std::pair<float, float> VALUES_AREA(-10.f, 10.f);

void StrokeTheFirstRemarkableLimit(const std::pair<float, float> border, const glm::ivec2 windowSize, const glm::ivec2 center, const float eps = 0.01f)
{
	const float STEP = eps;

	glColor3f(FUNCTION_COLOUR.x, FUNCTION_COLOUR.y, FUNCTION_COLOUR.z);
	glBegin(GL_LINE_STRIP);
	for (float x = border.first; x < border.second; x += STEP)
	{
		if (x - STEP >= 0 || x + STEP <= 0)
		{
			float y = sinf(x) / x;
			glVertex2f(center.x + x * SCALE.x / UNIT_INTERVAL.x * windowSize.x, center.y - y * SCALE.y / UNIT_INTERVAL.y * windowSize.y);
		}
		else
		{
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
	}
	glEnd();
	glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);
}

void DrawSegment(const glm::ivec2 point1, const glm::ivec2 point2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2d(point1.x, point1.y);
	glVertex2d(point2.x, point2.y);
	glEnd();
}

void StrokeCoordinateGrid(const glm::ivec2 windowSize)
{
	glColor3f(COORDINATE_SYSTEM_COLOUR.x, COORDINATE_SYSTEM_COLOUR.y, COORDINATE_SYSTEM_COLOUR.z);
	DrawSegment({ windowSize.x / 2, 0 }, { windowSize.x / 2, windowSize.y });
	DrawSegment({ 0, windowSize.y / 2 }, { windowSize.x, windowSize.y / 2 });
	glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);
}

void DrawUnitIntervals(const glm::ivec2 windowSize)
{
	glColor3f(UNIT_INTERVAL_COLOUR.x, UNIT_INTERVAL_COLOUR.y, UNIT_INTERVAL_COLOUR.z);

	for (float x = float(windowSize.x / 2); x <= windowSize.x; x += windowSize.x * 2 * SCALE.x )
	{
		DrawSegment({ windowSize.x - x, windowSize.y / 2 - 10 }, { windowSize.x - x, windowSize.y / 2 + 10 });
		DrawSegment({ x, windowSize.y / 2 - 10 }, { x, windowSize.y / 2 + 10 });
	}

	for (float y = float(windowSize.y / 2); y <= windowSize.y; y += windowSize.y * SCALE.y)
	{
		DrawSegment({ windowSize.x / 2 - 10, windowSize.y - y }, { windowSize.x / 2 + 10, windowSize.y - y });
		DrawSegment({ windowSize.x / 2 - 10, y }, { windowSize.x / 2 + 10, y });
	}

	glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);
}

void StrokeCartesianCoordinateSystem(const glm::ivec2 windowSize)
{
	StrokeCoordinateGrid(windowSize);	
	DrawUnitIntervals(windowSize);
}
}

CWindow::CWindow()
{
    SetBackgroundColor(BACKGROUND_COLOUR);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
    SetupView(size);

	StrokeTheFirstRemarkableLimit(VALUES_AREA, size, { size.x / 2, size.y / 2});
	StrokeCartesianCoordinateSystem(size);
}

void CWindow::SetupView(const glm::ivec2 & size)
{
    const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
