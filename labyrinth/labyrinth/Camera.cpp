#include "stdafx.h"
#include "Camera.h"

namespace
{

const float MOUSE_LINEAR_MOVE_SPEED = 0.25f;
const float MIN_DISTANCE = 1.f;
const float MAX_DISTANCE = 45.f;

}

CCamera::CCamera(float distance)
    :m_distance(distance)
{

}

void CCamera::Update(float deltaSec)
{
	(void)deltaSec;
    m_distance = glm::clamp(m_distance, MIN_DISTANCE, MAX_DISTANCE);
}

void CCamera::OnScale(const int & zoom)
{ 
	if (zoom > 0)
	{
		m_distance += -MOUSE_LINEAR_MOVE_SPEED;
	}
	else if (zoom < 0)
	{
		m_distance += MOUSE_LINEAR_MOVE_SPEED;
	}
}

glm::mat4 CCamera::GetViewTransform() const
{
	const auto eye = GetPosition();
    const glm::vec3 center = m_center;
	const glm::vec3 up = { 0, 0, 1 };

	return glm::lookAt(eye, center, up);
}

glm::vec3 CCamera::GetPosition() const
{
	glm::vec3 direction = { 1, 0, 0 };
#ifdef _DEBUG
	glm::vec3 eye = direction * m_distance;
#else
	glm::vec3 eye = direction;
#endif
	eye = glm::rotateZ(eye, glm::radians(float(-m_angle.y)));

	return eye;
}

void CCamera::SetRotationFlag(bool flag)
{
	m_doesRotate = flag;
}

bool CCamera::GetRotationFlag() const
{
	return m_doesRotate;
}

void CCamera::Rotate(const glm::vec2 angle)
{
	m_angle.x += angle.y;
	m_angle.y -= angle.x;
}

void CCamera::Translate(const glm::vec3 position)
{
	m_eye = position;
}
