#include "stdafx.h"

#include "IdentitySphere.h"

namespace
{

const unsigned MIN_PRECISION = 4;

void CalculateTriangleStripIndicies(std::vector<uint32_t> & indicies, unsigned columnCount, unsigned rowCount)
{
	indicies.clear();
	indicies.reserve((columnCount - 1) * rowCount * 2);

	for (unsigned ci = 0; ci < columnCount - 1; ++ci)
	{
		if (ci % 2 == 0)
		{
			for (unsigned ri = 0; ri < rowCount; ++ri)
			{
				unsigned index = ci * rowCount + ri;
				indicies.push_back(index + rowCount);
				indicies.push_back(index);
			}
		}
		else
		{
			for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
			{
				unsigned index = ci * rowCount + ri;
				indicies.push_back(index);
				indicies.push_back(index + rowCount);
			}
		}
	}
}

glm::vec3 GetPositionOnSphere(float u, float v)
{
	const float radius = 1.f;
	const float latitude = float(M_PI) * (1.f - v);
	const float longitude = float(2 * M_PI) * u;
	const float latitudeRadius = radius * sinf(latitude);

	return { cosf(longitude) * latitudeRadius,
	         cosf(latitude) * radius,
	         sinf(longitude) * latitudeRadius };
}

}

CIdentitySphere::CIdentitySphere(unsigned slices, unsigned stacks, const glm::vec3 & position)
{
	Tesselate(slices, stacks);
	std::transform(m_mesh.m_vertices.begin(), m_mesh.m_vertices.end(), m_mesh.m_vertices.begin(), [=](SVertexP3NT2 & vertex) {
		vertex.position += position;
		return vertex;
	});
}

void CIdentitySphere::Draw() const
{
	 m_mesh.Draw();
}

void CIdentitySphere::Tesselate(unsigned slices, unsigned stacks)
{
	assert((slices >= MIN_PRECISION) && (stacks >= MIN_PRECISION));

	m_mesh.Clear(MeshType::TriangleStrip);
	m_mesh.m_vertices.reserve(slices * stacks);
	
	for (unsigned ci = 0; ci < slices; ++ci)
	{
		const float u = float(ci) / float(slices - 1);
		for (unsigned ri = 0; ri < stacks; ++ri)
		{
			const float v = float(ri) / float(stacks - 1);

			SVertexP3NT2 vertex;
			vertex.position = GetPositionOnSphere(u, v);

			vertex.normal = vertex.position;
			vertex.texCoord = { 1.f - u, v };

			m_mesh.m_vertices.push_back(vertex);
		}
	}
	CalculateTriangleStripIndicies(m_mesh.m_indicies, slices, stacks);
}
