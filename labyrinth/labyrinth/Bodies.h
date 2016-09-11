#pragma once

#include "stdafx.h"

#include "IBody.h"
#include "Texture2D.h"

struct SVertexP3N
{
	glm::vec3 position;
	//glm::vec3 normal;
	glm::vec2 texCoord;

	SVertexP3N() = default;
	SVertexP3N(const glm::vec3 & position)
		:position(position)
	{

	}
};

class CIdentityCube final : public IBody
{
public:
    CIdentityCube();
    void Update(float deltaTime) final;
    void Draw() const final;

	void SetPosition(const glm::vec3 & position);
	glm::vec3 GetPosition() const;

	void SetSize(const glm::vec3 & size);
	glm::vec3 GetSize() const;

private:
    void OutputFaces() const;

	glm::vec3 m_position;
	glm::vec3 m_size;

	CTexture2DUniquePtr m_texture;

	std::vector<SVertexP3N> m_vertices;
	const std::vector<uint32_t> m_indicies;
};
