#pragma once

#include "libchapter3.h"
#include "MeshP3NT2.h"
#include "Cube.h"
#include "IRenderer3D.h"

class CBlock
{
public:
	CBlock() = default;
	CBlock(const glm::vec3 & center, const float size) { (void)center; (void)size; };
	virtual ~CBlock() = default;

	virtual void Update(const float dt) = 0;
	virtual void Draw(IRenderer3D & renderer) const = 0;

	virtual const CTexture2DAtlas & GetTexture2DAtlas() const = 0;

	//virtual bool CheckCollision(const glm::vec3 & position) const = 0;
};

enum class BlockType
{
	Barrier = 0,
	Free
};

class CBarrierBlock 
	:public CBlock
{
public:
	CBarrierBlock(const glm::vec3 & center, const float size);
	~CBarrierBlock() = default;

	void Update(const float dt) override;
	void Draw(IRenderer3D & renderer) const override;

	const CTexture2DAtlas & GetTexture2DAtlas() const override;

	//bool CheckCollision(const glm::vec3 & position) const override;

private:
	CCube m_cube;
	CTexture2DAtlas m_atlas;
	std::pair<glm::vec3, glm::vec3> m_position;
};

/*class CFreeBlock
	:public CBlock
{
public:
	CFreeBlock(const glm::vec3 & center, const float size);
	~CFreeBlock() = default;

	void Update(const float dt) override;
	void Draw() const override;

	bool CheckCollision(const glm::vec3 & position) const override;

private:
	CCube m_cube;
	CTexture2DAtlas m_atlas;
};*/
