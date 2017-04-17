#pragma once

#include "libchapter3.h"
#include "Camera.h"
#include "KeyboardController.h"

class CPlayer
{
public:
	CPlayer(CCamera & camera, CKeyboardController & keyboardHandler);
	~CPlayer() = default;

	void Update(const float dt);
	void Draw() const;
	void DispatchKeyboardEvent();

	glm::vec3 GetPosition() const;

private:
	CCamera & m_camera;
	CKeyboardController & m_keyboardHandler;
	glm::vec3 m_position;
};
