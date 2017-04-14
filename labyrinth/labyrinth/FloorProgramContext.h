#pragma once

#include "libchapter3.h"
#include "ProgramContext.h"

class CFloorProgramContext
	:public CProgramContext
{
public:
	CFloorProgramContext();

	void Use();

private:
	CTexture2DUniquePtr m_pTexture;
	CTexture2DUniquePtr m_pNormalTexture;
};
