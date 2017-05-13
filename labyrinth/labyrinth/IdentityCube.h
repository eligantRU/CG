#pragma once

#include "libchapter3.h"
#include "MeshP3NT2.h"
#include <array>

enum class CubeFace
{
	Front = 0,
	Back,
	Top,
	Bottom,
	Left,
	Right,

	NumFaces
};

class CIdentityCube
{
public:
	CIdentityCube();
	~CIdentityCube() = default;
	
	void Update(const float dt);
	void Draw(IRenderer3D & renderer) const;

private:
	void Triangulate();

	static const size_t FACES_COUNT = static_cast<size_t>(CubeFace::NumFaces);

	CMeshP3NT2 m_mesh;
	std::array<CFloatRect, FACES_COUNT> m_textureRects;
	bool m_isDirty = true;
};
