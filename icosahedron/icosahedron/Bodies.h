#pragma once

#include "stdafx.h"

class CIcosahedron
{
public:
	CIcosahedron();
	~CIcosahedron();
    void Update(float deltaTime);
	void Draw() const;

private:
	void DrawFaces() const;
	void DrawEdges() const;
};
