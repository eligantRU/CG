#pragma once

#include "libchapter3.h"
#include "BlockProgramContext.h"
#include "PhysWorld.h"

class CLabyrinth final
{
public:
	CLabyrinth(CPhysWorld & world);
	~CLabyrinth() = default;

	void Update(const float dt);
	void Draw();

	void SetModel(const glm::mat4 & value);
	void SetView(const glm::mat4 & value);
	void SetProjection(const glm::mat4 & value);
	void SetLight0(const SLightSource & source);

private:
	CPhysWorld & m_world;

	CBlockProgramContext m_blockContext;

	std::array<std::array<std::unique_ptr<CBlaCube>, 16>, 16> m_labyrinth;
};
