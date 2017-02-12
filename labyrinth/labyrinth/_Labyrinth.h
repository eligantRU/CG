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
	void Draw() const;

	bool CheckCollision(const glm::vec3 & position) const;

private:
	std::array<std::array<std::unique_ptr<CBlock>, 16>, 16> m_labyrinth;
	CFactory m_factory;
};