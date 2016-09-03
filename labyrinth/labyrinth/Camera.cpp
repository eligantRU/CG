#include "stdafx.h"
#include "Camera.h"

namespace
{

const float MOUSE_LINEAR_MOVE_SPEED = 0.025f;
const float MOVEMENT_SPEED = 0.1f;
const float MIN_DISTANCE = 1.f;
const float MAX_DISTANCE = 45.f;

}

CCamera::CCamera(glm::vec3 viewDirection, glm::vec3 eye, glm::vec3 up)
    :m_viewDirection(viewDirection)
	,m_eye(eye)
	,m_up(up)
{

}

void CCamera::Update(float deltaSec)
{
	(void)deltaSec;
}

void CCamera::OnScale(const int & zoom)
{ 
	(void)zoom;
}

glm::mat4 CCamera::GetViewTransform() const
{
	return glm::lookAt(m_eye, m_eye + m_viewDirection, m_up);
}

void CCamera::SetPosition(const glm::vec3 & position)
{
	m_eye = position;
}

glm::vec3 CCamera::GetPosition() const
{
	return m_eye;
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
	m_strafeDirection = glm::cross(m_viewDirection, m_up);
	glm::mat4 rotator = glm::rotate(-angle.x * MOUSE_LINEAR_MOVE_SPEED, m_up);
		//* glm::rotate(-angle.y * MOUSE_LINEAR_MOVE_SPEED, m_strafeDirection); // TODO: issue #11

	m_viewDirection = glm::mat3(rotator) * m_viewDirection;
}

void CCamera::MoveFrontal(const float speed)
{
	m_eye += speed * m_viewDirection;
}

void CCamera::StrafeLeft()
{
	m_eye += - MOVEMENT_SPEED * m_strafeDirection;
}

void CCamera::StrafeRight()
{
	m_eye += MOVEMENT_SPEED * m_strafeDirection;
}

void CCamera::MoveHorizontal(const float speed)
{
	m_eye -= speed * m_strafeDirection;
}

void CCamera::MoveVertical(const float speed)
{
	m_eye += speed * m_up;
}
