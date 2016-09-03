#pragma once

#include "stdafx.h"
#include "IBody.h"
#include "Camera.h"

class CPlayer : public IBody
{
public:
	CPlayer();
	~CPlayer();

	void Update(float deltaTime);
	void Draw() const;
	void DispatchKeyboardEvent(const SDL_KeyboardEvent & key);

	void SetCamera(std::shared_ptr<CCamera> camera);

	glm::vec3 GetPosition() const;

private:
	std::shared_ptr<CCamera> m_camera = nullptr;
	std::function<bool(glm::vec3 &)> m_fnCheckCollision;
	glm::vec3 m_position;
};
