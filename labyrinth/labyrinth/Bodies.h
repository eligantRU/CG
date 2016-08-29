#pragma once

#include "stdafx.h"
#include "IBody.h"

enum class CubeFace
{
    Front = 0,
    Back,
    Top,
    Bottom,
    Left,
    Right,

    NumFaces
};

struct SVertexP3N
{
	glm::vec3 position;
	glm::vec3 normal;

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

	void SetPosition(const glm::vec3 & pos);
	glm::vec3 GetPosition() const;

private:
    void OutputFaces() const;

    static const size_t COLORS_COUNT = static_cast<size_t>(CubeFace::NumFaces);
    glm::vec3 m_colors[COLORS_COUNT];
	glm::vec3 m_position;
	std::array<SVertexP3N, 8> m_vertices;
};
