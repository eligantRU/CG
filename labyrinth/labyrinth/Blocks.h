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

private:
	CCube m_cube;
	std::pair<glm::vec3, glm::vec3> m_position;
};
