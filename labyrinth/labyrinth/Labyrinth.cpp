#include "stdafx.h"

#include "Labyrinth.h"
#include "Renderer3D.h"

namespace
{

const float BLOCK_SIZE = 2.f;

const float BLOCK_MASS = 0.f;

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

template <class T>
void DoWithTransform(IProgramContext & context, const glm::mat4 & mat, T && callback)
{
	const auto was = context.GetView();
	context.SetView(was * mat);
	context.Use();
	callback();
	context.SetView(was);
}

}

CLabyrinth::CLabyrinth(CPhysWorld & world)
	:m_world(world)
{
	for (unsigned i = 0; i < m_labyrinth.size(); ++i)
	{
		for (unsigned j = 0; j < m_labyrinth[i].size(); ++j)
		{
			if (LABYRINTH[i][j] == 1)
			{
				float y = -float(m_labyrinth.size()) + i * BLOCK_SIZE;
				float z = -float(m_labyrinth.size()) + j * BLOCK_SIZE;
				float x = 1.f;

				auto block = std::make_unique<CBlaCube>(m_world, glm::vec3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE), glm::vec3(x, y, z), BLOCK_MASS);
				m_labyrinth[i][j] = std::move(block);
			}
		}
	}
}

void CLabyrinth::Update(const float dt)
{
	for (auto & row : m_labyrinth)
	{
		for (auto & block : row)
		{
			if (block != nullptr)
			{
				block->Update(dt);
			}
		}
	}
}

void CLabyrinth::Draw() // TODO: why non-const?
{
	CRenderer3D renderer(m_blockContext);
	for (const auto & row : m_labyrinth)
	{
		for (const auto & block : row)
		{
			if (block != nullptr)
			{
				block->Draw(renderer);
			}
		}
	}
}

void CLabyrinth::SetModel(const glm::mat4 & value)
{
	m_blockContext.SetModel(value);
}

void CLabyrinth::SetView(const glm::mat4 & value)
{
	m_blockContext.SetView(value);
}

void CLabyrinth::SetProjection(const glm::mat4 & value)
{
	m_blockContext.SetProjection(value);
}

void CLabyrinth::SetLight0(const SLightSource & source)
{
	m_blockContext.SetLight0(source);
}
