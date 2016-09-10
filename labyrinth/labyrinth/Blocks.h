#pragma once

#include "stdafx.h"
#include "IBody.h"
#include "Bodies.h"
#include "Texture2D.h"

class CBlock : public IBody
{
public:
	CBlock();
	virtual ~CBlock() = default;

	void Update(float deltaTime);
	void Draw() const;

	virtual void SetPosition(const glm::vec3 & position);
	glm::vec3 GetPosition() const;

	void SetSize(const glm::vec3 & size);
	glm::vec3 GetSize() const;

	virtual bool CheckCollision(const glm::vec3 & position) const = 0;

private:
	CIdentityCube m_cube; 
	CTexture2DUniquePtr m_texture;
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

	bool CheckCollision(const glm::vec3 & position) const override;

private:
};

class CFreeBlock : public CBlock
{
public:
	CFreeBlock();
	~CFreeBlock();

	void Draw() const override;

	void SetPosition(const glm::vec3 & position) override;
	bool CheckCollision(const glm::vec3 & position) const;

private:
	std::vector<SVertexP3N> m_vertices;
	const std::vector<uint32_t> m_indicies;
};
