#pragma once

#include "Blocks.h"

class CFactory // TODO: it is bad factory
{
public:
	CFactory() = default;
	~CFactory() = default;

	std::unique_ptr<CBlock> CreateBlock(const BlockType type, const glm::vec3 & center, const float size) const;

private:
	std::unique_ptr<CBarrierBlock> CreateBarrierBlock(const glm::vec3 & center, const float size) const;
	//std::unique_ptr<CFreeBlock> CreateFreeBlock(const glm::vec3 & center, const float size) const;
};
