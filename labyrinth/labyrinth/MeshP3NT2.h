#pragma once

#include <vector>
#include "libchapter3.h"

class IRenderer3D;

struct SVertexP3NT2
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct SMeshDataP3NT2
{
	std::vector<SVertexP3NT2> vertices;
	std::vector<uint32_t> indicies;
};

enum class MeshType
{
	Triangles,
	TriangleFan,
	TriangleStrip,
};

class CMeshP3NT2
	:private boost::noncopyable
{
public:
	CMeshP3NT2(MeshType meshType);

	void Copy(const SMeshDataP3NT2 & data);

	void Draw(IRenderer3D & renderer) const;

private:
	MeshType m_meshType;
	CBufferObject m_attributesBuffer;
	CBufferObject m_indexesBuffer;
	size_t m_verticiesCount = 0;
	size_t m_indiciesCount = 0;
};
