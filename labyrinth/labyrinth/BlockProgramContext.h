#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CBlockProgramContext
	:public CProgramContext
{
public:
	CBlockProgramContext(const CTexture2DAtlas & m_atlas);

	void Use();

private:
	const CTexture2DAtlas & m_atlas;
};
