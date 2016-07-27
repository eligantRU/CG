#pragma once

#include "stdafx.h"
#include "PhysicalObject.h"

class CRectangle : public CPhysicalObject
{
public:
	CRectangle() = default;
	~CRectangle() = default;

	void Draw() const override;

private:
};
