#include "stdafx.h"
#include "Camera.h"

namespace
{
const float MOUSE_LINEAR_MOVE_SPEED = 0.25f;
const float MIN_DISTANCE = 1.5f;
const float MAX_DISTANCE = 30.f;

}

CCamera::CCamera(float distance)
    :m_distance(distance)
	,m_angle(0, 0)
{

}

void CCamera::Update(float deltaSec)
{
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
	glm::vec3 direction = { 0, 1, 0 };
	
	glm::vec3 eye = direction * m_distance;
	glm::mat4 rotMatrix(1);
	rotMatrix = glm::rotate(rotMatrix, glm::radians(float(m_angle.first)), glm::vec3(1, 0, 0)); // TODO: Ask Shambir & fix the bug
	rotMatrix = glm::rotate(rotMatrix, glm::radians(float(m_angle.second)), glm::vec3(0, 0, -1));
	eye = glm::vec3(rotMatrix * glm::vec4(eye, 0.0));
    const glm::vec3 center = { 0, 0, 0 };
	const glm::vec3 up = { 0, 0, 1 };

	return glm::lookAt(eye, center, up);
}

glm::vec3 CCamera::GetPosition() const
{
	glm::vec3 direction = { 0, 1, 0 };

	glm::vec3 eye = direction * m_distance;
	glm::mat4 rotMatrix(1);
	rotMatrix = glm::rotate(rotMatrix, glm::radians(float(m_angle.first)), glm::vec3(1, 0, 0));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(float(m_angle.second)), glm::vec3(0, 0, -1));
	eye = glm::vec3(rotMatrix * glm::vec4(eye, 0.0));

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

void CCamera::SetAngle(int alpha, int beta)
{
	m_angle.first = alpha;
	m_angle.second = beta;
}

void CCamera::SetAngle(std::pair<int, int> angle)
{
	m_angle = angle;
}

std::pair<int, int> CCamera::GetAngle() const
{
	return m_angle;
}
