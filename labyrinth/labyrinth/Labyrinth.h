#pragma once

#include "libchapter2.h"
#include "Blocks.h"
#include "Factory.h"

class CLabyrinth final 
	:public ISceneObject
{
public:
	CLabyrinth();
	~CLabyrinth() = default;

	void Update(float dt) final;
	void Draw() const;

	bool CheckCollision(glm::vec3 position) const;

private:
	std::array<std::array<std::unique_ptr<CBlock>, 16>, 16> m_labyrinth;
	CFactory m_factory;
};
