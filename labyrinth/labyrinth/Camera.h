#pragma once

#include "stdafx.h"

class CCamera : private boost::noncopyable
{
public:
    explicit CCamera(float distance);

    void Update(float deltaSec);
	void OnScale(const int & zoom);

	glm::vec3 GetPosition() const;

	glm::mat4 GetViewTransform() const;

	void SetRotationFlag(bool flag);
	bool GetRotationFlag() const;

	void Rotate(const glm::vec2);
	void Translate(const glm::vec3);

private:
    float m_distance = 1;
	bool m_doesRotate = false;
	glm::vec2 m_angle;
	glm::vec3 m_eye;
	glm::vec3 m_center;
};
