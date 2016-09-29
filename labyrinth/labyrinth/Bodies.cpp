#include "stdafx.h"

#include "Bodies.h"
#include "Texture2D.h"
#include "consts.h"

namespace
{

const std::string BLOCK_TEXTURE_PATH = "res/block_texture.bmp";

const std::vector<uint32_t> CUBE_FACES = {
    0, 1, 2,
    0, 2, 3,
    2, 1, 5,
    2, 5, 6,
    3, 2, 6,
    3, 6, 7,
    0, 3, 7,
    0, 7, 4,
    1, 0, 4,
    1, 4, 5,
    6, 5, 4,
    6, 4, 7
};

template <class T>
void DoWithBindedArrays(const std::vector<SVertexP3N> & vertices, T && callback)
{
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	const size_t stride = sizeof(SVertexP3N);
	glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
	glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));
	//glTexCoordPointer(2, GL_FLOAT, stride, glm::value_ptr(vertices[0].texCoord));

	callback();

	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

}

CIdentityCube::CIdentityCube()
	:m_indicies(CUBE_FACES)
{
	m_vertices.reserve(8);
	m_texture = LoadTexture2DFromBMP(BLOCK_TEXTURE_PATH);
}

void CIdentityCube::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIdentityCube::Draw() const
{
	m_texture->DoWhileBinded([&] {
		OutputFaces();
	});
}

void CIdentityCube::SetPosition(const glm::vec3 & position)
{
	m_position = position;
	
	m_vertices.erase(m_vertices.begin(), m_vertices.end());
	m_vertices.push_back(SVertexP3N({ position.x - m_size.x / 2, position.y + m_size.y / 2, position.z - m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x + m_size.x / 2, position.y + m_size.y / 2, position.z - m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x + m_size.x / 2, position.y - m_size.y / 2, position.z - m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x - m_size.x / 2, position.y - m_size.y / 2, position.z - m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x - m_size.x / 2, position.y + m_size.y / 2, position.z + m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x + m_size.x / 2, position.y + m_size.y / 2, position.z + m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x + m_size.x / 2, position.y - m_size.y / 2, position.z + m_size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ position.x - m_size.x / 2, position.y - m_size.y / 2, position.z + m_size.z / 2 }));
}

glm::vec3 CIdentityCube::GetPosition() const
{
	return m_position;
}

void CIdentityCube::SetSize(const glm::vec3 & size)
{
	m_size = size;
}

glm::vec3 CIdentityCube::GetSize() const
{
	return m_size;
}

void CIdentityCube::OutputFaces() const
{
	/*DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLES, GLsizei(m_indicies.size()), GL_UNSIGNED_INT, m_indicies.data());
	});*/
}
