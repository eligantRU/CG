#include "stdafx.h"

#include "Factory.h"

CFactory::CFactory() = default;
CFactory::~CFactory() = default;

std::unique_ptr<CBlock> CFactory::CreateBlock(BlockType type) const
{
	switch (type)
	{
	case BlockType::Barrier:
		return CreateBarrierBlock();
	case BlockType::Free:
		return CreateFreeBlock();
	default:
		assert(0);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unexpected BlockType", nullptr);
		std::abort();
	}
}

std::unique_ptr<CBarrierBlock> CFactory::CreateBarrierBlock() const
{
	return std::make_unique<CBarrierBlock>();
}

std::unique_ptr<CFreeBlock> CFactory::CreateFreeBlock() const
{
	return std::make_unique<CFreeBlock>();
}
