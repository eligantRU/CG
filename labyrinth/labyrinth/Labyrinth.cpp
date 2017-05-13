#include "stdafx.h"

#include "Labyrinth.h"
#include "Renderer3D.h"

namespace
{

const auto BLOCK_SIDE = 1.f;
const glm::vec3 BLOCK_SIZE = { BLOCK_SIDE, BLOCK_SIDE, BLOCK_SIDE };

const auto BLOCK_MASS = 1.f;

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

template <class T, class TT>
void UpdateAndDraw(T & object, const glm::vec3 & size, CPhysWorld & world, TT & context, CRenderer3D & renderer)
{
	object->SetSizeScale(size);
	object->SetPosition(world.GetPosition(object->GetWorldIndex()));
	object->SetOrientation(world.GetOrientation(object->GetWorldIndex()));
	auto trans = object->ToMat4();
	DoWithTransform(context, trans, [&] {
		object->Draw(renderer);
	});
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
				float y = i * BLOCK_SIDE;
				float z = j * BLOCK_SIDE;
				float x = 0.f;

				m_labyrinth[i][j] = std::make_unique<CCubeEntity>(m_world, 0.5f * BLOCK_SIDE, glm::vec3(x, y, z), BLOCK_MASS);
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

void CLabyrinth::Draw() const
{
	CRenderer3D renderer(m_blockContext);
	for (const auto & row : m_labyrinth)
	{
		for (const auto & block : row)
		{
			if (block != nullptr)
			{
				UpdateAndDraw(block, BLOCK_SIZE, m_world, m_blockContext, renderer);
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
