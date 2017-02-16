#include "stdafx.h"

#include "Labyrinth.h"
#include "Blocks.h"

namespace
{

const float BLOCK_SIZE = 2;

const std::vector<std::vector<int>> LABYRINTH = { // TODO: load from image-file
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

}

CLabyrinth::CLabyrinth()
{
	for (unsigned i = 0; i < m_labyrinth.size(); ++i)
	{
		for (unsigned j = 0; j < m_labyrinth[i].size(); ++j)
		{
			float x = - float(m_labyrinth.size()) + i * BLOCK_SIZE;
			float y = - float(m_labyrinth.size()) + j * BLOCK_SIZE;
			float z = 0;

			auto block = m_factory.CreateBlock(BlockType::Barrier, glm::vec3(x, y, z), BLOCK_SIZE);
			m_labyrinth[i][j] = std::move(block);
		}
	}
}

void CLabyrinth::Update(const float dt)
{
	for (auto & row : m_labyrinth)
	{
		for (auto & block : row)
		{
			block->Update(dt);
		}
	}
}

void CLabyrinth::Draw(IRenderer3D & renderer) const
{
	for (const auto & row : m_labyrinth)
	{
		for (const auto & element : row)
		{
			element->Draw(renderer);
		}
	}
}

