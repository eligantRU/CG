#include "stdafx.h"

#include "Player.h"

namespace
{

	const glm::vec3 INITIAL_POSITION = { 0, 0, 0 };
	const float MOUSE_LINEAR_MOVE_SPEED = 0.25f;

}

CPlayer::CPlayer()
	:m_position(INITIAL_POSITION)
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

void CPlayer::SetCamera(std::shared_ptr<CCamera> camera)
{
	m_camera = camera;
}

void CPlayer::DispatchKeyboardEvent(const SDL_KeyboardEvent & key)
{
	switch (key.keysym.sym)
	{
	case SDLK_w:
		m_position.x += MOUSE_LINEAR_MOVE_SPEED;
		break;
	case SDLK_a:
		m_position.y += MOUSE_LINEAR_MOVE_SPEED;
		break;
	case SDLK_s:
		m_position.x -= MOUSE_LINEAR_MOVE_SPEED;
		break;
	case SDLK_d:
		m_position.y -= MOUSE_LINEAR_MOVE_SPEED;
		break;
	}
	m_camera->Translate(m_position);
}
