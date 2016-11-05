#include "stdafx.h"

#include "Player.h"

namespace
{

const glm::vec3 INITIAL_POSITION = { 0, 0, 0 };
const float MOVEMENT_SPEED = 0.04f;
const float JUMP_VELOCITY = 2.5f;
const float ACCELERATION = 0.1f;

}

CPlayer::CPlayer(CCamera & camera, CKeyboardHandler & keyboardHandler)
	:m_position(INITIAL_POSITION)
	,m_camera(camera)
	,m_keyboardHandler(keyboardHandler)
{

}

CPlayer::~CPlayer() = default;

void CPlayer::Update(float dt)
{
	(void)dt;

	if (m_deltaHeight < 0)
	{
		m_deltaHeight = 0;
		m_verticalVelocity = 0;
		auto pos = m_camera.GetPosition();
		m_camera.SetPosition({ pos.x, pos.y, 0 });
		return;
	}

	if ((m_verticalVelocity > 0) && (m_deltaHeight >= 0))
	{
		m_deltaHeight += m_verticalVelocity * dt;
		m_verticalVelocity -= ACCELERATION;
		
		auto pos = m_camera.GetPosition();
		m_camera.SetPosition({ pos.x, pos.y, pos.z + m_deltaHeight });
	}
	else if ((m_verticalVelocity <= 0) && (m_deltaHeight > 0))
	{
		m_deltaHeight += m_verticalVelocity * dt;
		m_verticalVelocity -= ACCELERATION;

		auto pos = m_camera.GetPosition();
		m_camera.SetPosition({ pos.x, pos.y, pos.z - m_deltaHeight });
	}
}

void CPlayer::Draw() const
{

}

glm::vec3 CPlayer::GetPosition() const
{
	return m_position;
}

float CPlayer::GetDeltaHeight() const
{
	return m_deltaHeight;
}

float CPlayer::GetVerticalVelocity() const
{
	return m_verticalVelocity;
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
	if (m_keyboardHandler.IsKeyPressed(SDLK_SPACE) && (m_deltaHeight == 0))
	{
		m_verticalVelocity = JUMP_VELOCITY;
	}
	m_position = m_camera.GetPosition();
}
