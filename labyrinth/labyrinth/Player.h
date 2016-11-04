#pragma once

#include "libchapter2.h"
#include "Camera.h"
#include "KeyboardHandler.h"

class CPlayer 
	:public ISceneObject
{
public:
	CPlayer(CCamera & camera, CKeyboardHandler & keyboardHandler);
	~CPlayer();

	void Update(float deltaTime);
	void Draw() const;
	void DispatchKeyboardEvent();

	glm::vec3 GetPosition() const;

private:
	CCamera & m_camera;
	CKeyboardHandler & m_keyboardHandler;
	std::function<bool(glm::vec3 &)> m_fnCheckCollision;
	glm::vec3 m_position;
};
