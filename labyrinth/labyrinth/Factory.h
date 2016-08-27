#pragma once

#include "stdafx.h"
#include "Blocks.h"

class CFactory
{
public:
	CFactory();
	~CFactory();

	std::unique_ptr<CBlock> CreateBlock(BlockType type) const;

private:
	std::unique_ptr<CBarrierBlock> CreateBarrierBlock() const;
	std::unique_ptr<CFreeBlock> CreateFreeBlock() const;
};
