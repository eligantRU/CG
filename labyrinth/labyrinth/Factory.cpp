#include "stdafx.h"

#include "Factory.h"

std::unique_ptr<CBlock> CFactory::CreateBlock(const BlockType type, const glm::vec3 & center, const float size) const
{
	switch (type)
	{
	case BlockType::Barrier:
		return CreateBarrierBlock(center, size);
	case BlockType::Free:
		return CreateFreeBlock(center, size);
	default:
		assert(0);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unexpected BlockType", nullptr); // TODO: use boost::variant
		std::abort();
	}
}

std::unique_ptr<CBarrierBlock> CFactory::CreateBarrierBlock(const glm::vec3 & center, const float size) const
{
	return std::make_unique<CBarrierBlock>(center, size);
}

std::unique_ptr<CFreeBlock> CFactory::CreateFreeBlock(const glm::vec3 & center, const float size) const
{
	return std::make_unique<CFreeBlock>(center, size);
}
