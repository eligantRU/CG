#pragma once

#include "stdafx.h"

class CCamera : private boost::noncopyable
{
public:
    explicit CCamera(float rotationRadians, float distance);

    void Update(float deltaSec);
    bool OnKeyDown(const SDL_KeyboardEvent & event);
    bool OnKeyUp(const SDL_KeyboardEvent & event);
	bool OnScale(const int & zoom);

    glm::mat4 GetViewTransform() const;

private:
    float m_rotationRadians = 0;
    float m_distance = 1;
    std::set<unsigned> m_keysPressed;
};
