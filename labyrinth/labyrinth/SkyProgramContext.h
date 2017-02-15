#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CSkyProgramContext
	:public CProgramContext
{
public:
	CSkyProgramContext();

	void Use();

private:
	CTexture2DUniquePtr m_pTexture;
};

