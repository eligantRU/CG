#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CMoonProgramContext
	:public CProgramContext
{
public:
	CMoonProgramContext();

	void Use();

private:
	CTexture2DUniquePtr m_pTexture;
	CTexture2DUniquePtr m_pNormalTexture;
};
