#include "stdafx.h"
#include "Camera.h"

namespace
{

const float MOUSE_LINEAR_MOVE_SPEED = 0.25f;
const float MIN_DISTANCE = 2.5f;
const float MAX_DISTANCE = 200.f;

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

	return glm::lookAt(eye, center, up);
}

glm::vec3 CCamera::GetPosition() const
{
	glm::vec3 direction = { 0, 1, 0 };

	glm::vec3 eye = direction * m_distance;
	glm::mat4 rotMatrix(1);
	// rotMatrix = glm::rotate(rotMatrix, glm::radians(float(m_angle.x)), glm::vec3(1, 0, 0)); // on the fan :)
	rotMatrix = glm::rotate(rotMatrix, glm::radians(float(m_angle.y)), glm::vec3(0, 0, -1));
	eye = glm::vec3(rotMatrix * glm::vec4(eye, 1));

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
