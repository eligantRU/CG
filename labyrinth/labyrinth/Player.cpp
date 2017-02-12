#include "stdafx.h"

#include "Player.h"

namespace
{

const glm::vec3 INITIAL_POSITION = { 0, 0, 0 };
const float MOVEMENT_SPEED = 0.03f;

}

CPlayer::CPlayer(CCamera & camera, CKeyboardHandler & keyboardHandler)
	:m_position(INITIAL_POSITION)
	,m_camera(camera)
	,m_keyboardHandler(keyboardHandler)
{

}

void CPlayer::Update(const float dt)
{
	(void)&dt;
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
	auto k = 1.f;
	if (m_keyboardHandler.IsKeyPressed(SDLK_LSHIFT))
	{
		k = 2.f;
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_w))
	{
		m_camera.MoveFrontal(k * MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_s))
	{
		m_camera.MoveFrontal(-k * MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_a))
	{
		m_camera.MoveHorizontal(k * MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_d))
	{
		m_camera.MoveHorizontal(-k * MOVEMENT_SPEED);
	}
	m_position = m_camera.GetPosition();
}
