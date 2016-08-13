#pragma once

#include "stdafx.h"

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

class CIdentityCube
{
public:
    CIdentityCube();
    void Update(float deltaTime);
    void Draw() const;

    void SetFaceColor(CubeFace face, const glm::vec3 & color);

private:
    static const size_t COLORS_COUNT = static_cast<size_t>(CubeFace::NumFaces);
    glm::vec3 m_colors[COLORS_COUNT];
};
