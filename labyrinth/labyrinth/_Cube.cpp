#include "stdafx.h"

#include "Cube.h"

namespace
{

struct SCubeFace
{
	uint16_t vertexIndex1;
	uint16_t vertexIndex2;
	uint16_t vertexIndex3;
	uint16_t vertexIndex4;
	uint16_t faceIndex;
};

const SCubeFace CUBE_FACES[] = {
	{ 2, 3, 0, 1, static_cast<uint16_t>(CubeFace::Front) },
	{ 6, 2, 1, 5, static_cast<uint16_t>(CubeFace::Left) },
	{ 6, 7, 3, 2, static_cast<uint16_t>(CubeFace::Bottom) },
	{ 3, 7, 4, 0, static_cast<uint16_t>(CubeFace::Right) },
	{ 1, 0, 4, 5, static_cast<uint16_t>(CubeFace::Top) },
	{ 5, 4, 7, 6, static_cast<uint16_t>(CubeFace::Back) }
};

}

CCube::CCube(const glm::vec3 & center, const float size)
{
	m_verticies = {
		glm::vec3(center.x - size / 2, center.y + size / 2, center.z - size / 2),
		glm::vec3(center.x + size / 2, center.y + size / 2, center.z - size / 2),
		glm::vec3(center.x + size / 2, center.y - size / 2, center.z - size / 2),
		glm::vec3(center.x - size / 2, center.y - size / 2, center.z - size / 2),
		glm::vec3(center.x - size / 2, center.y + size / 2, center.z + size / 2),
		glm::vec3(center.x + size / 2, center.y + size / 2, center.z + size / 2),
		glm::vec3(center.x + size / 2, center.y - size / 2, center.z + size / 2),
		glm::vec3(center.x - size / 2, center.y - size / 2, center.z + size / 2)
	};
}

void CCube::Update(float)
{
	if (m_isDirty)
	{
		Triangulate();
		m_isDirty = false;
	}
}

void CCube::Draw() const
{
	m_mesh.Draw();
}

void CCube::SetFaceTextureRect(CubeFace face, const CFloatRect & rect)
{
	const size_t index = static_cast<size_t>(face);
	m_textureRects[index] = rect;
	m_isDirty = true;
}

void CCube::Triangulate()
{
	m_mesh.Clear(MeshType::Triangles);
	for (const SCubeFace &face : CUBE_FACES)
	{
		const CFloatRect texRect = m_textureRects[face.faceIndex];
		const glm::vec3 &coord1 = m_verticies[face.vertexIndex1];
		const glm::vec3 &coord2 = m_verticies[face.vertexIndex2];
		const glm::vec3 &coord3 = m_verticies[face.vertexIndex3];
		const glm::vec3 &coord4 = m_verticies[face.vertexIndex4];
		const glm::vec3 normal = glm::normalize(glm::cross(coord2 - coord1, coord3 - coord1));

		const SVertexP3NT2 v1 = { coord1, texRect.GetTopLeft(), normal };
		const SVertexP3NT2 v2 = { coord2, texRect.GetTopRight(), normal };
		const SVertexP3NT2 v3 = { coord3, texRect.GetBottomRight(), normal };
		const SVertexP3NT2 v4 = { coord4, texRect.GetBottomLeft(), normal };

		const uint32_t fromIndex = uint32_t(m_mesh.m_vertices.size());
		m_mesh.m_vertices.push_back(v1);
		m_mesh.m_vertices.push_back(v2);
		m_mesh.m_vertices.push_back(v3);
		m_mesh.m_vertices.push_back(v4);
		m_mesh.m_indicies.push_back(fromIndex + 0);
		m_mesh.m_indicies.push_back(fromIndex + 1);
		m_mesh.m_indicies.push_back(fromIndex + 2);
		m_mesh.m_indicies.push_back(fromIndex + 0);
		m_mesh.m_indicies.push_back(fromIndex + 2);
		m_mesh.m_indicies.push_back(fromIndex + 3);
	}
}
