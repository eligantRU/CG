#include "stdafx.h"

#include "Player.h"

namespace
{

const glm::vec3 INITIAL_POSITION = { 0, 0, 0 };
const float MOUSE_LINEAR_MOVE_SPEED = 0.25f; 
const float MOVEMENT_SPEED = 0.15f;

}

CPlayer::CPlayer(CCamera & camera)
	:m_position(INITIAL_POSITION)
	,m_camera(camera)
{

}

CPlayer::~CPlayer() = default;

void CPlayer::Update(float deltaTime)
{
	(void)deltaTime;
}

void CPlayer::Draw() const
{

}

glm::vec3 CPlayer::GetPosition() const
{
	return m_position;
}

void CPlayer::DispatchKeyboardEvent(const SDL_KeyboardEvent & key)
{
	switch (key.keysym.sym)
	{
	case SDLK_w:
		m_camera.MoveFrontal(MOVEMENT_SPEED);
		break;
	case SDLK_s:
		m_camera.MoveFrontal(-MOVEMENT_SPEED);
		break;
	case SDLK_a:
		m_camera.MoveHorizontal(MOVEMENT_SPEED);
		break;
	case SDLK_d:
		m_camera.MoveHorizontal(-MOVEMENT_SPEED);
		break;
	default:
		break;
	}
	m_position = m_camera.GetPosition();
}
