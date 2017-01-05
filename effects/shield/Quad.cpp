#include "stdafx.h"

#include "libchapter3.h"
#include "Quad.h"

static const float MAX_TEX_COORD = 4.f;

namespace
{

template <class T>
void DoWithBindedArrays(const std::vector<SVertexP2T2> & vertices, T && callback)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	const size_t stride = sizeof(SVertexP2T2);
	glVertexPointer(2, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));
	glTexCoordPointer(2, GL_FLOAT, stride, glm::value_ptr(vertices[0].texCoord));

	callback();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

}

CQuad::CQuad(const glm::vec2 &leftTop, const glm::vec2 & size)
{
	SVertexP2T2 vLeftTop = { leftTop, glm::vec2(0, 0) };
	SVertexP2T2 vRightTop = { leftTop + glm::vec2(size.x, 0.f), glm::vec2(MAX_TEX_COORD, 0) };
	SVertexP2T2 vLeftBottom = { leftTop + glm::vec2(0, size.y), glm::vec2(0, MAX_TEX_COORD) };
	SVertexP2T2 vRightBottom = { leftTop + size, glm::vec2(MAX_TEX_COORD, MAX_TEX_COORD) };

	m_vertices = { vLeftTop, vRightTop, vLeftBottom, vRightBottom };
	m_indicies = { 0, 1, 2, 1, 3, 2 };
}

void CQuad::Draw() const
{
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLES, GLsizei(m_indicies.size()),
		               GL_UNSIGNED_BYTE, m_indicies.data());
	});
}
