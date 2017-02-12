#pragma once

#include "libchapter3.h"
#include "Camera.h"
#include "KeyboardHandler.h"

class CPlayer
{
public:
	CPlayer(CCamera & camera, CKeyboardHandler & keyboardHandler);
	~CPlayer() = default;

	void Update(const float dt);
	void Draw() const;
	void DispatchKeyboardEvent();

	glm::vec3 GetPosition() const;

private:
	CCamera & m_camera;
	CKeyboardHandler & m_keyboardHandler;
	glm::vec3 m_position;
};
