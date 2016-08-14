#pragma once

#include "stdafx.h"

class CIcosahedron
{
public:
	CIcosahedron();
	~CIcosahedron();
    void Update(float deltaTime);
    void Draw() const;
	void DrawEdges() const;

private:
};
