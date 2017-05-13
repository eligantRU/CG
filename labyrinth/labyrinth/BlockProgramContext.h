#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CBlockProgramContext
	:public CProgramContext
{
public:
	CBlockProgramContext();

	void Use();

	const CTexture2DAtlas & GetAtlas() const;

private:
	CTexture2DAtlas m_atlas;
	CTexture2DAtlas m_normalAtlas;
};
