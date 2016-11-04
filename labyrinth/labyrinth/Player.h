#pragma once

#include "libchapter2.h"
#include "Camera.h"

class CPlayer 
	:public ISceneObject
{
public:
	CPlayer(CCamera & camera);
	~CPlayer();

	void Update(float deltaTime);
	void Draw() const;
	void DispatchKeyboardEvent(const SDL_KeyboardEvent & key);

	glm::vec3 GetPosition() const;

private:
	CCamera & m_camera;
	std::function<bool(glm::vec3 &)> m_fnCheckCollision;
	glm::vec3 m_position;
};
