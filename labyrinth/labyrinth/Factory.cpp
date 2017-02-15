#include "stdafx.h"

#include "Factory.h"

std::unique_ptr<CBlock> CFactory::CreateBlock(const BlockType type, const glm::vec3 & center, const float size) const
{
	switch (type) // TODO: fix logic error
	{
	case BlockType::Barrier:
	case BlockType::Free:
		return CreateBarrierBlock(center, size);
		//return CreateFreeBlock(center, size);
	default:
		throw std::logic_error("Unexpected BlockType");
	}
}

std::unique_ptr<CBarrierBlock> CFactory::CreateBarrierBlock(const glm::vec3 & center, const float size) const
{
	return std::make_unique<CBarrierBlock>(center, size);
}

/*std::unique_ptr<CFreeBlock> CFactory::CreateFreeBlock(const glm::vec3 & center, const float size) const
{
	return std::make_unique<CFreeBlock>(center, size);
}*/
