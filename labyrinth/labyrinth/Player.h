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

	void SetCamera(std::shared_ptr<CCamera> camera);
	void DispatchKeyboardEvent(const SDL_KeyboardEvent & key);

private:
	std::shared_ptr<CCamera> m_camera = nullptr;
	glm::vec3 m_position;
};
