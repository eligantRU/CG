#include "stdafx.h"

#include "Blocks.h"

namespace
{

const char COBBLESTONE_TEXTURE_ATLAS[] = "res/cobblestone_block/cobblestone_block.plist";
const std::pair<CubeFace, const char *> COBBLESTONE_FRAME_MAPPING[] = {
	{ CubeFace::Front, "cobblestone_block_front.png" },
	{ CubeFace::Back, "cobblestone_block_back.png" },
	{ CubeFace::Top, "cobblestone_block_top.png" },
	{ CubeFace::Bottom, "cobblestone_block_bottom.png" },
	{ CubeFace::Left, "cobblestone_block_left.png" },
	{ CubeFace::Right, "cobblestone_block_right.png" }
};

const char GRASS_TEXTURE_ATLAS[] = "res/grass_block/grass_block.plist";
const std::pair<CubeFace, const char *> GRASS_FRAME_MAPPING[] = {
	{ CubeFace::Front, "grass_block_front.png" },
	{ CubeFace::Back, "grass_block_back.png" },
	{ CubeFace::Top, "grass_block_top.png" },
	{ CubeFace::Bottom, "grass_block_bottom.png" },
	{ CubeFace::Left, "grass_block_left.png" },
	{ CubeFace::Right, "grass_block_right.png" }
};

CTexture2DLoader MakeTextureLoader()
{
	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::CLAMP_TO_EDGE);
	return loader;
}

}

CBarrierBlock::CBarrierBlock(const glm::vec3 & center, const float size)
	:m_atlas(CFilesystemUtils::GetResourceAbspath(COBBLESTONE_TEXTURE_ATLAS), MakeTextureLoader())
	,m_cube(center, size)
	,m_position(glm::vec3(center.x - size, center.y - size, center.z - size), glm::vec3(center.x + size, center.y + size, center.z + size))
{
	for (const auto &pair : COBBLESTONE_FRAME_MAPPING)
	{
		CFloatRect texRect = m_atlas.GetFrameRect(pair.second);
		m_cube.SetFaceTextureRect(pair.first, texRect);
	}
}

void CBarrierBlock::Update(float dt)
{
	m_cube.Update(dt);
}

void CBarrierBlock::Draw() const
{
	m_atlas.GetTexture().DoWhileBinded([this] {
		m_cube.Draw();
	});
}

bool CBarrierBlock::CheckCollision(const glm::vec3 & position) const
{
	auto eps = 0.85f;
	if ((m_position.first.x + eps <= position.x && position.x <= m_position.second.x - eps) &&
		(m_position.first.y + eps <= position.y && position.y <= m_position.second.y - eps) &&
		(m_position.first.z + eps <= position.z && position.z <= m_position.second.z - eps))
	{
		return true;
	}
	return false;
}

CFreeBlock::CFreeBlock(const glm::vec3 & center, const float size)
	:m_atlas(CFilesystemUtils::GetResourceAbspath(GRASS_TEXTURE_ATLAS), MakeTextureLoader())
	,m_cube(glm::vec3(center.x, center.y, center.z - 2), size)
{
	for (const auto &pair : GRASS_FRAME_MAPPING)
	{
		CFloatRect texRect = m_atlas.GetFrameRect(pair.second);
		m_cube.SetFaceTextureRect(pair.first, texRect);
	}
}

void CFreeBlock::Draw() const
{
	m_atlas.GetTexture().DoWhileBinded([this] {
		m_cube.Draw();
	});
}

void CFreeBlock::Update(float dt)
{
	m_cube.Update(dt);
}

bool CFreeBlock::CheckCollision(const glm::vec3 & position) const
{
	(void)position;
	return false;
}
