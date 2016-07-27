#pragma once

#include "stdafx.h"

class CPhysicalObject
{
public:
	CPhysicalObject() = default;
	virtual ~CPhysicalObject() = default;

	virtual void SetPosition(glm::vec2 position);
	glm::vec2 GetPosition() const;
	
	void SetRotation(float angle);
	float GetRotation() const;

	void SetWeight(float weight);
	float GetWeight() const;

	void SetSize(glm::vec2 size);
	glm::vec2 GetSize() const;

	virtual void Draw() const = 0;

	void SetData(unsigned);
	unsigned GetData() const;

private:
	glm::vec2 m_position;
	float m_angle = 0;
	float m_weight = 0;
	glm::vec2 m_size;
	unsigned m_id = 0;
};
