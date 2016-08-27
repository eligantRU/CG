#pragma once

#include "stdafx.h"

class CCamera : private boost::noncopyable
{
public:
    explicit CCamera(float distance);

    void Update(float deltaSec);
	bool OnScale(const int & zoom);

	glm::vec3 GetPosition() const;

	glm::mat4 GetViewTransform() const;

	void SetRotationFlag(bool flag);
	bool GetRotationFlag() const;

	void Rotate(const glm::vec2);

private:
    float m_distance = 1;
	bool m_doesRotate = false;
	glm::vec2 m_angle;
};
