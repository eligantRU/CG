#include "stdafx.h"

#include "Blocks.h"

CBlock::CBlock() = default;

CBlock::~CBlock() = default;

void CBlock::Update(float deltaTime)
{
	(void)deltaTime;
}

void CBlock::Draw() const
{
	m_cube.Draw();
}

CBarrierBlock::CBarrierBlock() = default;

CBarrierBlock::~CBarrierBlock() = default;

void CBarrierBlock::Draw() const
{

}

CFreeBlock::CFreeBlock() = default;

CFreeBlock::~CFreeBlock() = default;

void CFreeBlock::Draw() const
{
	CBlock::Draw();
}
