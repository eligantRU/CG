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
	// TODO: i? j? 16?
	for (unsigned i = 0; i < 16; ++i)
	{
		for (unsigned j = 0; j < 16; ++j)
		{
			float x = - float(m_labyrinth.size()) + i * BLOCK_SIZE;
			float y = - float(m_labyrinth.size()) + j * BLOCK_SIZE;
			float z = 0;

			auto type = ((LABYRINTH[i][j])) ? BlockType::Barrier : BlockType::Free;
			auto block = m_factory.CreateBlock(type, glm::vec3(x, y, z), BLOCK_SIZE);
			m_labyrinth[i][j] = std::move(block);
		}
	}
}

void CLabyrinth::Update(float dt)
{
	for (auto &row : m_labyrinth)
	{
		for (auto &block : row)
		{
			block->Update(dt);
		}
	}
}

void CLabyrinth::Draw() const
{
	for (const auto &row : m_labyrinth)
	{
		for (const auto &element : row)
		{
			element->Draw();
		}
	}
}

bool CLabyrinth::CheckCollision(const glm::vec3 & position) const
{
	for (const auto &row : m_labyrinth)
	{
		for (const auto &element : row)
		{
			if (!element->CheckCollision(position))
			{
				return false;
			}
		}
	}
	return true;
}
