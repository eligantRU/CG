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

class CCube final
{
public:
	CCube();
	CCube(const glm::vec3 & center, const float size);
	~CCube() = default; 
	
	void Update(const float dt);
	void Draw(IRenderer3D & renderer) const;

	const CTexture2DAtlas & GetTexture2DAtlas() const;

	void SetFaceTextureRect(CubeFace face, const CFloatRect & rect);

private:
	void Triangulate();

	static const size_t FACES_COUNT = static_cast<size_t>(CubeFace::NumFaces);

	CMeshP3NT2 m_mesh;
	std::array<CFloatRect, FACES_COUNT> m_textureRects;
	CTexture2DAtlas m_atlas;
	bool m_isDirty = true;
	std::array<glm::vec3, 8> m_verticies;
};
