#include "stdafx.h"

#include "Labyrinth.h"

namespace
{

	const glm::vec3 BLOCK_SIZE = { 1, 1, 1 };

}

CLabyrinth::CLabyrinth()
{
	for (unsigned i = 0; i < m_labyrinth.size(); ++i)
	{
		for (unsigned j = 0; j < m_labyrinth.size(); ++j)
		{
			float x = - float(m_labyrinth.size()) + i * BLOCK_SIZE.x * 2;
			float y = - float(m_labyrinth.size()) + j * BLOCK_SIZE.y * 2;
			float z = 0;

			m_labyrinth[i][j].SetPosition({ x, y, z});
		}
	}
}

CLabyrinth::~CLabyrinth() = default;

void CLabyrinth::Draw() const
{
	for (const auto bla : m_labyrinth) // TODO: no bla
	{
		for (const auto bla : bla) // TODO: no bla
		{
			bla.Draw();
		}
	}
}
