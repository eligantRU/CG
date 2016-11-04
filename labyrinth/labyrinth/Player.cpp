#include "stdafx.h"

#include "Player.h"

namespace
{

const glm::vec3 INITIAL_POSITION = { 0, 0, 0 };
const float MOUSE_LINEAR_MOVE_SPEED = 0.25f; 
const float MOVEMENT_SPEED = 0.15f;

}

CPlayer::CPlayer(CCamera & camera, CKeyboardHandler & keyboardHandler)
	:m_position(INITIAL_POSITION)
	,m_camera(camera)
	,m_keyboardHandler(keyboardHandler)
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

void CPlayer::DispatchKeyboardEvent()
{
	if (m_keyboardHandler.IsKeyPressed(SDLK_w))
	{
		m_camera.MoveFrontal(MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_s))
	{
		m_camera.MoveFrontal(-MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_a))
	{
		m_camera.MoveHorizontal(MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_d))
	{
		m_camera.MoveHorizontal(-MOVEMENT_SPEED);
	}
	m_position = m_camera.GetPosition();
}
