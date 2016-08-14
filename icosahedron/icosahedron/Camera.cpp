#include "stdafx.h"
#include "Camera.h"

namespace
{
const float ROTATION_SPEED_RADIANS = 0.001f;
const float LINEAR_MOVE_SPEED = 0.003f;
const float MOUSE_LINEAR_MOVE_SPEED = 0.25f;
const float MIN_DISTANCE = 1.5f;
const float MAX_DISTANCE = 30.f;

bool ShouldTrackKeyPressed(const SDL_Keysym & key)
{
    switch (key.sym)
    {
    case SDLK_LEFT:
    case SDLK_RIGHT:
    case SDLK_UP:
    case SDLK_DOWN:
    case SDLK_w:
    case SDLK_a:
    case SDLK_s:
    case SDLK_d:
        return true;
    }
    return false;
}

float GetRotationSpeedRadians(std::set<unsigned> & keysPressed)
{
    if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
    {
        return ROTATION_SPEED_RADIANS;
    }
    if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
    {
        return -ROTATION_SPEED_RADIANS;
    }
    return 0;
}

float GetLinearMoveSpeed(std::set<unsigned> & keysPressed)
{
    if (keysPressed.count(SDLK_UP) || keysPressed.count(SDLK_w))
    {
        return -LINEAR_MOVE_SPEED;
    }
    if (keysPressed.count(SDLK_DOWN) || keysPressed.count(SDLK_s))
    {
        return +LINEAR_MOVE_SPEED;
    }
    return 0;
}

}

CCamera::CCamera(float rotationRadians, float distance)
    :m_rotationRadians(rotationRadians)
    ,m_distance(distance)
	,m_angle(0, 0)
{

}

void CCamera::Update(float deltaSec)
{ // TODO: use deltaSec!
    m_rotationRadians += /*deltaSec * */ GetRotationSpeedRadians(m_keysPressed);
    m_distance += /*deltaSec * */ GetLinearMoveSpeed(m_keysPressed);
    m_distance = glm::clamp(m_distance, MIN_DISTANCE, MAX_DISTANCE);
}

bool CCamera::OnScale(const int & zoom)
{ // TODO: use deltaSec!
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
	glm::vec3 direction = { 1, 0, 0 };
	
	const glm::vec3 eye = direction * m_distance;
    const glm::vec3 center = { 0, 0, 0 };
	const glm::vec3 up = { 0, 0, 1 };

    return glm::lookAt(eye, center, up) * glm::rotate(glm::mat4(), glm::radians(float(m_angle.first)), { 0, 1, 0 })
										* glm::rotate(glm::mat4(), glm::radians(float(m_angle.second)), { 0, 0, -1 });
}

glm::vec3 CCamera::GetPosition() const
{
	glm::vec3 direction = { 1, 0, 0 };
	direction = glm::rotateZ(glm::normalize(direction), glm::radians(float(m_angle.second)));

	return direction * m_distance;
}

void CCamera::OnRotate()
{
	m_rotationRadians += ROTATION_SPEED_RADIANS;
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
