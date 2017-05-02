#include "stdafx.h"

#include "IdentityCube.h"

namespace
{

const auto CUBE_SIZE = 0.5f;

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

CIdentityCube::CIdentityCube()
	:m_mesh(MeshType::Triangles)
{
	m_verticies = {
		glm::vec3(-CUBE_SIZE / 2, +CUBE_SIZE / 2, -CUBE_SIZE / 2),
		glm::vec3(+CUBE_SIZE / 2, +CUBE_SIZE / 2, -CUBE_SIZE / 2),
		glm::vec3(+CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2),
		glm::vec3(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2),
		glm::vec3(-CUBE_SIZE / 2, +CUBE_SIZE / 2, +CUBE_SIZE / 2),
		glm::vec3(+CUBE_SIZE / 2, +CUBE_SIZE / 2, +CUBE_SIZE / 2),
		glm::vec3(+CUBE_SIZE / 2, -CUBE_SIZE / 2, +CUBE_SIZE / 2),
		glm::vec3(-CUBE_SIZE / 2, -CUBE_SIZE / 2, +CUBE_SIZE / 2)
	};
}

void CIdentityCube::Update(const float dt)
{
	(void)&dt;
	if (m_isDirty)
	{
		Triangulate();
		m_isDirty = false;
	}
}

void CIdentityCube::Draw(IRenderer3D & renderer) const
{
	m_mesh.Draw(renderer);
}

void CIdentityCube::Triangulate()
{
	SMeshDataP3NT2 mesh;
	for (const SCubeFace & face : CUBE_FACES)
	{
		const CFloatRect texRect = m_textureRects[face.faceIndex];
		const glm::vec3 & coord1 = m_verticies[face.vertexIndex1];
		const glm::vec3 & coord2 = m_verticies[face.vertexIndex2];
		const glm::vec3 & coord3 = m_verticies[face.vertexIndex3];
		const glm::vec3 & coord4 = m_verticies[face.vertexIndex4];
		const glm::vec3 normal = glm::normalize(glm::cross(coord2 - coord1, coord3 - coord1));

		// TODO: fix these crutches
		const SVertexP3NT2 v1 = { coord1, {0, 0}, normal };
		const SVertexP3NT2 v2 = { coord2, {0, 1}, normal };
		const SVertexP3NT2 v3 = { coord3, {1, 1}, normal };
		const SVertexP3NT2 v4 = { coord4, {1, 0}, normal };
		/*const SVertexP3NT2 v1 = { coord1, texRect.GetTopLeft(), normal };
		const SVertexP3NT2 v2 = { coord2, texRect.GetTopRight(), normal };
		const SVertexP3NT2 v3 = { coord3, texRect.GetBottomRight(), normal };
		const SVertexP3NT2 v4 = { coord4, texRect.GetBottomLeft(), normal };*/

		const uint32_t fromIndex = uint32_t(mesh.vertices.size());
		mesh.vertices.push_back(v1);
		mesh.vertices.push_back(v2);
		mesh.vertices.push_back(v3);
		mesh.vertices.push_back(v4);
		mesh.indicies.push_back(fromIndex + 0);
		mesh.indicies.push_back(fromIndex + 1);
		mesh.indicies.push_back(fromIndex + 2);
		mesh.indicies.push_back(fromIndex + 0);
		mesh.indicies.push_back(fromIndex + 2);
		mesh.indicies.push_back(fromIndex + 3);
	}
	m_mesh.Copy(mesh);
}
