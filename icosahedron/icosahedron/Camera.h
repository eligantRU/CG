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

	void SetAngle(int, int);
	void SetAngle(std::pair<int, int>);
	std::pair<int, int> GetAngle() const;

private:
    float m_distance = 1;
    std::set<unsigned> m_keysPressed;
	bool m_doesRotate = false;
	std::pair<int, int> m_angle;
};
