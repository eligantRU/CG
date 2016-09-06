#include "stdafx.h"

#include "Blocks.h"

namespace
{

const std::vector<uint32_t> CUBE_FACES = {
	0, 2, 1,
	0, 3, 2,
	6, 4, 5,
	6, 7, 4
};

template <class T>
void DoWithBindedArrays(const std::vector<SVertexP3N> & vertices, T && callback)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	const size_t stride = sizeof(SVertexP3N);
	//glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
	glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

	callback();

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
}

}

CBlock::CBlock() = default;

void CBlock::Update(float deltaTime)
{
	(void)deltaTime;
}

void CBlock::SetPosition(const glm::vec3 & position)
{
	m_cube.SetPosition(position);
}

glm::vec3 CBlock::GetPosition() const
{
	return m_cube.GetPosition();
}

void CBlock::SetSize(const glm::vec3 & size)
{
	m_cube.SetSize(size);
}

glm::vec3 CBlock::GetSize() const
{
	return m_cube.GetSize();
}

void CBlock::Draw() const
{
	m_cube.Draw();
}

CBarrierBlock::CBarrierBlock() = default;

CBarrierBlock::~CBarrierBlock() = default;

void CBarrierBlock::Draw() const
{
	CBlock::Draw();
}

bool CBarrierBlock::CheckCollision(glm::vec3 & position) const
{
	auto pos = GetPosition();
	auto size = GetSize();
	const std::vector<glm::vec3> vertices = {
		{ pos.x - size.x / 2, pos.y + size.y / 2, pos.z - size.z / 2 },
		{ pos.x + size.x / 2, pos.y + size.y / 2, pos.z - size.z / 2 },
		{ pos.x + size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 },
		{ pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 },
		{ pos.x - size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 },
		{ pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 },
		{ pos.x + size.x / 2, pos.y - size.y / 2, pos.z + size.z / 2 },
		{ pos.x - size.x / 2, pos.y - size.y / 2, pos.z + size.z / 2 }
	};

	auto eps = 0.1f;
	if ((vertices[3].x - eps <= position.x && position.x <= vertices[5].x + eps) && 
		(vertices[3].y - eps <= position.y && position.y <= vertices[5].y + eps) &&
		(vertices[3].z - eps <= position.z && position.z <= vertices[5].z + eps))
	{
		return true;
	}
	return false;
}

CFreeBlock::CFreeBlock()
	:m_indicies(CUBE_FACES)
{
	m_vertices.reserve(8);
}

CFreeBlock::~CFreeBlock() = default;

void CFreeBlock::SetPosition(const glm::vec3 & position)
{
	CBlock::SetPosition(position);
	
	auto pos = position;
	auto size = CBlock::GetSize();
	m_vertices.erase(m_vertices.begin(), m_vertices.end());
	m_vertices.push_back(SVertexP3N({ pos.x - size.x / 2, pos.y + size.y / 2, pos.z - size.z / 2 })),
	m_vertices.push_back(SVertexP3N({ pos.x + size.x / 2, pos.y + size.y / 2, pos.z - size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ pos.x + size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ pos.x - size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ pos.x + size.x / 2, pos.y - size.y / 2, pos.z + size.z / 2 }));
	m_vertices.push_back(SVertexP3N({ pos.x - size.x / 2, pos.y - size.y / 2, pos.z + size.z / 2 }));
}

void CFreeBlock::Draw() const
{
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLES, GLsizei(m_indicies.size()), GL_UNSIGNED_INT, m_indicies.data());
	});
}

bool CFreeBlock::CheckCollision(glm::vec3 & position) const
{
	(void)position;
	return false;
}
