#include "stdafx.h"
#include "Bodies.h"

namespace
{
	
typedef glm::vec3 Vertex;

struct STriangleFace
{
    uint16_t vertexIndex1;
    uint16_t vertexIndex2;
    uint16_t vertexIndex3;
    uint16_t colorIndex;
};

const Vertex CUBE_VERTICIES[] = {
    { -1, +1, -1 },
    { +1, +1, -1 },
    { +1, -1, -1 },
    { -1, -1, -1 },
    { -1, +1, +1 },
    { +1, +1, +1 },
    { +1, -1, +1 },
    { -1, -1, +1 },
};

const STriangleFace CUBE_FACES[] = {
    { 0, 1, 2, static_cast<uint16_t>(CubeFace::Back) },
    { 0, 2, 3, static_cast<uint16_t>(CubeFace::Back) },
    { 2, 1, 5, static_cast<uint16_t>(CubeFace::Right) },
    { 2, 5, 6, static_cast<uint16_t>(CubeFace::Right) },
    { 3, 2, 6, static_cast<uint16_t>(CubeFace::Bottom) },
    { 3, 6, 7, static_cast<uint16_t>(CubeFace::Bottom) },
    { 0, 3, 7, static_cast<uint16_t>(CubeFace::Left) },
    { 0, 7, 4, static_cast<uint16_t>(CubeFace::Left) },
    { 1, 0, 4, static_cast<uint16_t>(CubeFace::Top) },
    { 1, 4, 5, static_cast<uint16_t>(CubeFace::Top) },
    { 6, 5, 4, static_cast<uint16_t>(CubeFace::Front) },
    { 6, 4, 7, static_cast<uint16_t>(CubeFace::Front) },
};

}

CIdentityCube::CIdentityCube()
    :m_alpha(1)
{
    for (glm::vec3 &color : m_colors)
    {
        color.x = 1;
        color.y = 1;
        color.z = 1;
    }
}

void CIdentityCube::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIdentityCube::Draw() const
{
    if (m_alpha < 0.99f)
    {
        glFrontFace(GL_CW);
        OutputFaces();
        glFrontFace(GL_CCW);
    }
    OutputFaces();
}

void CIdentityCube::SetFaceColor(CubeFace face, const glm::vec3 & color)
{
    const size_t index = static_cast<size_t>(face);
    assert(index < COLORS_COUNT);
    m_colors[index] = color;
}

void CIdentityCube::SetAlpha(float alpha)
{
    m_alpha = alpha;
}

void CIdentityCube::OutputFaces() const // TODO: do not do it this way
{
    glBegin(GL_TRIANGLES);

    for (const STriangleFace &face : CUBE_FACES)
    {
        const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
        const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
        const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
        glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        glm::vec3 color = m_colors[face.colorIndex];

        glColor4f(color.x, color.y, color.z, m_alpha);
        glNormal3fv(glm::value_ptr(normal));
        glVertex3fv(glm::value_ptr(v1));
        glVertex3fv(glm::value_ptr(v2));
        glVertex3fv(glm::value_ptr(v3));
    }
    glEnd();
}
