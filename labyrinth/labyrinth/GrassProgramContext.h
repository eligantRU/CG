#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CGrassProgramContext
	:public CProgramContext
{
public:
	CGrassProgramContext();

	void Use();

private:
	CTexture2DUniquePtr m_pTexture;
	CTexture2DUniquePtr m_pNormalTexture;
};
