#pragma once

#include "stdafx.h"
#include "IBody.h"
#include "Blocks.h"
#include "Factory.h"
#include "consts.h"

class CLabyrinth final : public IBody
{
public:
	CLabyrinth(); // TODO: get sth with barriers & roads
	~CLabyrinth();

	void Update(float) final { };
	void Draw() const;

private:
	std::array<std::array<std::unique_ptr<CBlock>, 16>, 16> m_labyrinth;
	CFactory m_factory;
};
