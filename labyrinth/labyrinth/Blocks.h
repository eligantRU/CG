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

	void SetPosition(const glm::vec3 & position);
	glm::vec3 GetPosition() const;

	void SetSize(const glm::vec3 & size);
	glm::vec3 GetSize() const;

	virtual bool CheckCollision(glm::vec3 & position) const = 0;

private:
	CIdentityCube m_cube;
};

enum class BlockType
{
	Barrier = 0,
	Free
};

class CBarrierBlock : public CBlock
{
public:
	CBarrierBlock();
	~CBarrierBlock();

	void Draw() const override;

	bool CheckCollision(glm::vec3 & position) const;

private:
};

class CFreeBlock : public CBlock
{
public:
	CFreeBlock();
	~CFreeBlock();

	void Draw() const override;

	bool CheckCollision(glm::vec3 & position) const;

private:
};
