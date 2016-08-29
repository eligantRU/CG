#include "stdafx.h"

#include "Blocks.h"

namespace
{

	typedef glm::vec3 Vertex;

	struct STriangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
	};

	const Vertex FREE_BLOCK_VERTICIES[] = {
		{ -1, +1, -1 },
		{ +1, +1, -1 },
		{ +1, -1, -1 },
		{ -1, -1, -1 },
		{ -1, +1, +1 },
		{ +1, +1, +1 },
		{ +1, -1, +1 },
		{ -1, -1, +1 },
	};

	const STriangleFace FREE_BLOCK_FACES[] = {
		{ 0, 2, 1},
		{ 0, 3, 2},
		{ 6, 4, 5},
		{ 6, 7, 4}
	};

}

CBlock::CBlock() = default;

CBlock::~CBlock() = default;

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

void CBlock::Draw() const
{
	auto pos = GetPosition();
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z); // TODO: do not use glTranslatef()
	m_cube.Draw();
	glPopMatrix();
}

CBarrierBlock::CBarrierBlock() = default;

CBarrierBlock::~CBarrierBlock() = default;

void CBarrierBlock::Draw() const
{
	CBlock::Draw();
}

CFreeBlock::CFreeBlock() = default;

CFreeBlock::~CFreeBlock() = default;

void CFreeBlock::Draw() const // TODO: this is the wrong way
{
	glPushMatrix();

	auto pos = GetPosition();
	glTranslatef(pos.x, pos.y, pos.z); // TODO: do not use glTranslatef()

	glBegin(GL_TRIANGLES);
	for (const STriangleFace &face : FREE_BLOCK_FACES)
	{
		const Vertex &v1 = FREE_BLOCK_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = FREE_BLOCK_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = FREE_BLOCK_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		glColor3f(0, 0, 0);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();

	glPopMatrix();
}
