#pragma once

#include "stdafx.h"
#include "IBody.h"
#include "Blocks.h"

class CLabyrinth final : public IBody
{
public:
	CLabyrinth(); // TODO: get sth with barriers & roads
	~CLabyrinth();

	void Update(float) final { };
	void Draw() const;

private:
	std::array<std::array<CBlock, 16>, 16> m_labyrinth;
};
