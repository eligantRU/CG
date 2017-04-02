#pragma once

#include <array>

#include "libchapter3.h"
#include "MeshP3NT2.h"

enum class RectangleFace
{
	Front = 0,
	Back,

	NumFaces
};

class CRectangle
{
public:
	CRectangle();
	CRectangle(const glm::vec2 & topLeft, const glm::vec2 & bottomRight);
	~CRectangle() = default;

	void Update(const float dt);
	void Draw(IRenderer3D & renderer) const;

	void SetFaceTextureRect(RectangleFace face, const CFloatRect & rect);

private:
	void Triangulate();

	CMeshP3NT2 m_mesh;
	bool m_isDirty = true;
	std::array<CFloatRect, 2> m_textureRects;
	std::array<glm::vec3, 4> m_verticies;
};
