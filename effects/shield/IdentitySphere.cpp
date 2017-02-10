#include "stdafx.h"
#include "IdentitySphere.h"
#include <algorithm>

namespace
{

struct CSphereTesselator : SMeshDataP3NT2
{
public:
	static const unsigned MIN_PRECISION = 4;

	void Tesselate(unsigned slices, unsigned stacks)
	{
		assert((slices >= MIN_PRECISION) && (stacks >= MIN_PRECISION));
		MakeVertexAttributes(slices, stacks);
		MakeTriangleStripIndicies(slices, stacks);
	}

private:
	void MakeVertexAttributes(unsigned columnCount, unsigned rowCount)
	{
		// вычисляем позиции вершин.
		for (unsigned ci = 0; ci < columnCount; ++ci)
		{
			const float u = float(ci) / float(columnCount - 1);
			for (unsigned ri = 0; ri < rowCount; ++ri)
			{
				const float v = float(ri) / float(rowCount - 1);

				SVertexP3NT2 vertex;
				vertex.position = GetPositionOnSphere(u, v);
				vertex.normal = vertex.position;
				vertex.texCoord = { 1.f - u, v };

				vertices.push_back(vertex);
			}
		}
	}

	void MakeTriangleStripIndicies(unsigned columnCount, unsigned rowCount)
	{
		indicies.clear();
		indicies.reserve((columnCount - 1) * rowCount * 2);
		// вычисляем индексы вершин.
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

	glm::vec3 GetPositionOnSphere(float u, float v)const
	{
		const float radius = 1.f;
		const float latitude = float(M_PI) * (1.f - v);
		const float longitude = float(2.0 * M_PI) * u;
		const float latitudeRadius = radius * sinf(latitude);

		return{ cosf(longitude) * latitudeRadius,
			cosf(latitude) * radius,
			sinf(longitude) * latitudeRadius };
	}
};

}

CIdentitySphere::CIdentitySphere(unsigned slices, unsigned stacks)
	:m_mesh(MeshType::TriangleStrip)
{
	CSphereTesselator tesselator;
	tesselator.Tesselate(slices, stacks);
	m_mesh.Copy(tesselator);
}

void CIdentitySphere::Draw(IRenderer3D & renderer) const
{
	m_mesh.Draw(renderer);
}
