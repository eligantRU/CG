#pragma once

#include "libchapter3.h"
#include "Blocks.h"
#include "Factory.h"
#include "BlockProgramContext.h"

class CLabyrinth final
{
public:
	CLabyrinth();
	~CLabyrinth() = default;

	void Update(const float dt);
	void Draw();

	void SetModel(const glm::mat4 & value);
	void SetView(const glm::mat4 & value);
	void SetProjection(const glm::mat4 & value);
	void SetLight0(const SLightSource & source);

private:
	CBlockProgramContext m_blockContext;

	std::array<std::array<std::unique_ptr<CBlock>, 16>, 16> m_labyrinth;
	CFactory m_factory;
};
