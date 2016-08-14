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
	std::vector<std::pair<unsigned, unsigned>> m_edges;
};
