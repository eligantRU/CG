#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CBlockProgramContext
	:public CProgramContext
{
public:
	CBlockProgramContext();

	void Use();

private:
	CTexture2DAtlas m_atlas;
};
