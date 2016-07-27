#pragma once

#include "stdafx.h"
#include "PhysicalObject.h"

class CCircle : public CPhysicalObject
{
public:
	CCircle() = default;
	~CCircle() = default;

	void Draw() const override;

	void SetRadius(float radius);
	float GetRadius() const;

private:
	float m_radius = 0;
};
