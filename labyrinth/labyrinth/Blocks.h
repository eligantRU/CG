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
	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition() const;

	void Draw() const;
private:
	CIdentityCube m_cube;
	glm::vec3 m_position;
};

class CBarrierBlock : public CBlock
{
public:
	CBarrierBlock();
	~CBarrierBlock();

	void Draw() const override;
private:
};

class CFreeBlock : public CBlock
{
public:
	CFreeBlock();
	~CFreeBlock();

	void Draw() const override;
private:
};
