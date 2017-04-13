#pragma once

// TODO: rename it

#include "libchapter3.h"
#include "ProgramContext.h"

class CNormalMapping
	:public CProgramContext
{
public:
	CNormalMapping();

	void Use();

private:
	CTexture2DUniquePtr m_pTexture;
	CTexture2DUniquePtr m_pNormalMap;
};
