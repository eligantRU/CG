#include "Rectangle.h"

namespace
{

struct SRectangleFace
{
	uint16_t vertexIndex1;
	uint16_t vertexIndex2;
	uint16_t vertexIndex3;
	uint16_t vertexIndex4;
	uint16_t faceIndex;
};

const SRectangleFace RECTANGLE_FACES[] = {
	{ 0, 1, 2, 3, static_cast<uint16_t>(RectangleFace::Front) },
	{ 1, 0, 3, 2, static_cast<uint16_t>(RectangleFace::Back) }
};

}

CRectangle::CRectangle()
	:CRectangle(glm::vec2(-1, +1), glm::vec2(+1, -1))
{

}

CRectangle::CRectangle(const glm::vec2 & topLeft, const glm::vec2 & bottomRight)
	:m_mesh(MeshType::Triangles)
{
	m_textureRects[0] = CFloatRect(topLeft, bottomRight);
	m_textureRects[1] = CFloatRect(bottomRight, topLeft);

	m_verticies = {
		glm::vec3(topLeft.x, topLeft.y, 0),
		glm::vec3(topLeft.x, bottomRight.y, 0),
		glm::vec3(bottomRight.x, bottomRight.y, 0),
		glm::vec3(bottomRight.x, topLeft.y, 0),
	};
}

void CRectangle::Update(const float dt)
{
	(void)&dt;
	if (m_isDirty)
	{
		Triangulate();
		m_isDirty = false;
	}
}

void CRectangle::Draw(IRenderer3D & renderer) const
{
	m_mesh.Draw(renderer);
}

void CRectangle::SetFaceTextureRect(RectangleFace face, const CFloatRect & rect)
{
	const size_t index = static_cast<size_t>(face);
	m_textureRects[index] = rect;
	m_isDirty = true;
}

void CRectangle::Triangulate()
{
	SMeshDataP3NT2 mesh;
	for (const SRectangleFace & face : RECTANGLE_FACES)
	{
		const CFloatRect texRect = m_textureRects[face.faceIndex];
		const glm::vec3 & coord1 = m_verticies[face.vertexIndex1];
		const glm::vec3 & coord2 = m_verticies[face.vertexIndex2];
		const glm::vec3 & coord3 = m_verticies[face.vertexIndex3];
		const glm::vec3 & coord4 = m_verticies[face.vertexIndex4];
		const glm::vec3 normal = glm::normalize(glm::cross(coord2 - coord1, coord3 - coord1));

		const SVertexP3NT2 v1 = { coord1, texRect.GetTopLeft(), normal };
		const SVertexP3NT2 v2 = { coord2, texRect.GetTopRight(), normal };
		const SVertexP3NT2 v3 = { coord3, texRect.GetBottomRight(), normal };
		const SVertexP3NT2 v4 = { coord4, texRect.GetBottomLeft(), normal };

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

