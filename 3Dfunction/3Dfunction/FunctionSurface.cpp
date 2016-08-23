#include "stdafx.h"
#include "FunctionSurface.h"

namespace
{

const float DOT_SIZE = 5.f;

glm::vec3 GetPosition(const Function3D & fn, float u, float v)
{
	return fn(u, v);
}

void CalculateNormals(std::vector<SVertexP3NT2> & vertices, const Function3D & fn, float step)
{
	for (SVertexP3NT2 &v : vertices)
	{
		const glm::vec3 & position = v.position;
		const auto & uv = v.uv;
		glm::vec3 dir1 = GetPosition(fn, uv.x, uv.y + step) - position;
		glm::vec3 dir2 = GetPosition(fn, uv.x + step, uv.y) - position;
		v.normal = glm::normalize(glm::cross(dir1, dir2));
	}
}

template <class T> 
void DoWithBindedArrays(const std::vector<SVertexP3NT2> & vertices, T && callback)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    const size_t stride = sizeof(SVertexP3NT2);
    glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
    glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

    callback();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

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

}

CSolidFunctionSurface::CSolidFunctionSurface(const Function2D & fn)
{
	m_fn = [=](float x, float z) {
		return glm::vec3(x, fn(x,z), z);
	};
}

CSolidFunctionSurface::CSolidFunctionSurface(const Function3D & fn)
	:m_fn(fn)
{

}

void CSolidFunctionSurface::Tesselate(const glm::vec2 & rangeX, const glm::vec2 & rangeZ, float step)
{
    const unsigned columnCount = unsigned((rangeX.y - rangeX.x) / step);
    const unsigned rowCount = unsigned((rangeZ.y - rangeZ.x) / step);
    m_vertices.clear();
    m_vertices.reserve(columnCount * rowCount);

    for (unsigned ci = 0; ci < columnCount; ++ci)
    {
        const float u = rangeX.x + step * float(ci);
        for (unsigned ri = 0; ri < rowCount; ++ri)
        {
            const float v = rangeZ.x + step * float(ri);

			m_vertices.push_back(SVertexP3NT2(GetPosition(m_fn, u, v), { u, v }));
        }
    }
    CalculateNormals(m_vertices, m_fn, step);
    CalculateTriangleStripIndicies(m_indicies, columnCount, rowCount);
}

void CSolidFunctionSurface::Draw() const
{
	DrawFace();
}

void CSolidFunctionSurface::DrawFace() const
{
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()), GL_UNSIGNED_INT, m_indicies.data());
	});
}