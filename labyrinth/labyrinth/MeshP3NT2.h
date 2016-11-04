#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

enum class MeshType
{
	Triangles,
	TriangleFan,
	TriangleStrip
};

struct SVertexP3NT2
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct SMeshP3NT2
{
	std::vector<SVertexP3NT2> m_vertices;
	std::vector<uint32_t> m_indicies;
	MeshType m_meshType = MeshType::Triangles;

	void Clear(MeshType meshType);

	void Draw() const;
};
