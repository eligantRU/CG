#pragma once

#include "libchapter2.h"
#include "Camera.h"
#include "KeyboardHandler.h"

class CPlayer 
	:public ISceneObject
{
public:
	CPlayer(CCamera & camera, CKeyboardHandler & keyboardHandler);
	~CPlayer() = default;

	void Update(float dt);
	void Draw() const;
	void DispatchKeyboardEvent();

	glm::vec3 GetPosition() const;
	float GetDeltaHeight() const;
	float GetVerticalVelocity() const;

private:
	CCamera & m_camera;
	CKeyboardHandler & m_keyboardHandler;
	glm::vec3 m_position;

	float m_verticalVelocity = 0;
	float m_deltaHeight = 0;
};
