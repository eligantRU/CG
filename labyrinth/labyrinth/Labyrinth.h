#pragma once

#include "libchapter3.h"
#include "Blocks.h"
#include "Factory.h"

class CLabyrinth final
{
public:
	CLabyrinth();
	~CLabyrinth() = default;

	void Update(const float dt);
	void Draw(IRenderer3D & renderer) const;

private:
	std::array<std::array<std::unique_ptr<CBlock>, 32>, 32> m_labyrinth;
	CFactory m_factory;
};
