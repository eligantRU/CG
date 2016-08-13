#include "stdafx.h"
#include "Bodies.h"

namespace
{

const glm::vec4 BLACK = { 0, 0, 0, 1 };
const glm::vec3 YELLOW = { 1.f, 1.f, 0.f };
const glm::vec3 ORANGE = { 1.f, 0.5f, 0.f };
const glm::vec3 PINK = { 1.f, 0.3f, 0.3f };

typedef glm::vec3 Vertex;

const Vertex CUBE_VERTICIES[] = {
    /*{-1, +1, -1},
    {+1, +1, -1},
    {+1, -1, -1},
    {-1, -1, -1},
    {-1, +1, +1},
    {+1, +1, +1},
    {+1, -1, +1},
    {-1, -1, +1},*/

	{ 0, 1, 0 },
	{ 0.951f, 0.5f, -0.309f },
	{ 0.587f, 0.5f, 0.809f },
	{ -0.587f, 0.5f, 0.809f },
	{ -0.951f, 0.5f, -0.309f },
	{ 0, 0.5f, -1 },
	{ 0.951f, -0.5f, 0.309f },
	{ 0, -0.5f, 1 },
	{ -0.951f, -0.5f, 0.309f },
	{ -0.587f, -0.5f, -0.809f },
	{ 0.587f, -0.5f, -0.809f },
	{ 0, -1, 0 }
};

struct STriangleFace
{
    uint16_t vertexIndex1;
    uint16_t vertexIndex2;
    uint16_t vertexIndex3;
	glm::vec3 vertexColor;
};

const STriangleFace CUBE_FACES[] = {
	{ 0, 2, 1, { 0.25f, 0.25f, 0.25f } },
	{ 0, 3, 2, { 0, 0, 1 } },
	{ 0, 5, 4, { 0, 1, 0 } },
	{ 0, 4, 3, { 0, 1, 1 } },
	{ 0, 4, 3, { 1, 0, 0 } },
	{ 0, 5, 4, { 1, 0, 1 } },
	{ 0, 1, 5, { 1, 1, 0 } },
	{ 6, 1, 7, { 1, 1, 1 } },
	{ 7, 1, 2, { 0, 0, 0.5f } },
	{ 7, 2, 8, { 0, 0.5f, 0 } },
	{ 8, 2, 3, { 0, 0.5f, 0.5f } },
	{ 8, 3, 9, { 0.5f, 0, 0 } },
	{ 9, 3, 4, { 0.5f, 0, 0.5f } },
	{ 9, 4, 10, { 0.5f, 0.5f, 0 } },
	{ 10, 4, 5, { 0.5f, 0.5f, 0.5f } },

	{ 10, 5, 6, { 0, 0, 0.75f } },
	{ 6, 5, 1, { 0, 0.75f, 0 } },
	{ 7, 11, 6, { 0, 0.75f, 0.75f } },
	{ 8, 11, 7, { 0.75f, 0, 0 } },
	{ 9, 11, 8, { 0.75f, 0, 0.75f } },
	{ 10, 11, 9, { 0.75f, 0.75f, 0 } },
	{ 6, 11, 10, { 0.75f, 0.75f, 0.75f } }
};

}

CIcosahedron::CIcosahedron()
{

}

CIcosahedron::~CIcosahedron() = default;

void CIcosahedron::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIcosahedron::Draw() const
{
    glBegin(GL_TRIANGLES);

    for (const STriangleFace &face : CUBE_FACES)
    {
        const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
        const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
        const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
        glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		
		glColor3fv(glm::value_ptr(glm::vec3(face.vertexColor)));
        glNormal3fv(glm::value_ptr(normal));
        glVertex3fv(glm::value_ptr(v1));
        glVertex3fv(glm::value_ptr(v2));
        glVertex3fv(glm::value_ptr(v3));
    }
    glEnd();
}
