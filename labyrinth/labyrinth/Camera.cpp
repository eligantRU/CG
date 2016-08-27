#include "stdafx.h"
#include "Camera.h"

namespace
{

const float MOUSE_LINEAR_MOVE_SPEED = 0.25f;
const float MIN_DISTANCE = 1.f;
const float MAX_DISTANCE = 40.f;

}

CCamera::CCamera(float distance)
    :m_distance(distance)
	,m_angle(0, 0)
{

}

void CCamera::Update(float deltaSec)
{
	(void)deltaSec;
    m_distance = glm::clamp(m_distance, MIN_DISTANCE, MAX_DISTANCE);
}

bool CCamera::OnScale(const int & zoom)
{ 
	if (zoom > 0)
	{
		m_distance += -MOUSE_LINEAR_MOVE_SPEED;
		return true;
	}
	else if (zoom < 0)
	{
		m_distance += MOUSE_LINEAR_MOVE_SPEED;
		return true;
	}
	return false;
}

glm::mat4 CCamera::GetViewTransform() const
{
	const auto eye = GetPosition();
    const glm::vec3 center = { 0, 0, 0 };
	const glm::vec3 up = { 0, 0, 1 };

	return glm::lookAt(eye, center, up) * glm::rotate(glm::mat4(), glm::radians(float(m_angle.x)), glm::vec3(0, 1, 0))
										* glm::rotate(glm::mat4(), glm::radians(float(m_angle.y)), glm::vec3(0, 0, -1));
}

glm::vec3 CCamera::GetPosition() const
{
	glm::vec3 direction = { 1, 0, 0 };

	glm::vec3 eye = direction * m_distance;

	// eye = glm::rotate(eye, glm::radians(float(m_angle.x)), glm::vec3(0, 1, 0));
	// eye = glm::rotate(eye, glm::radians(float(m_angle.y)), glm::vec3(0, 0, -1));

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
	m_angle.y += angle.x;
}
