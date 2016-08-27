#pragma once

#include "stdafx.h"
#include "IBody.h"
#include "Bodies.h"

class CBlock : public IBody
{
public:
	CBlock();
	~CBlock();

	void Update(float deltaTime);

	void Draw() const;
private:
	CIdentityCube m_cube;
};

class CBarrierBlock : public CBlock
{
public:
	CBarrierBlock();
	~CBarrierBlock();

	void Draw() const override;
private:
};

class CFreeBlock : public CBlock
{
public:
	CFreeBlock();
	~CFreeBlock();

	void Draw() const override;
private:
};
