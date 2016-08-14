#include "stdafx.h"
#include "Bodies.h"

namespace
{

typedef glm::vec3 Vertex;

const Vertex ICOSAHEDRON_VERTICIES[] = {
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
	glm::vec4 vertexColor;
};

const STriangleFace ICOSAHEDRON_FACES[] = {
	{ 0, 2, 1, { 0.75f, 0.25f, 0.5f, 0.5f } },
	{ 0, 3, 2, { 0, 0, 1, 0.5f } },
	{ 0, 5, 4, { 0, 1, 0, 0.5f } },
	{ 0, 4, 3, { 1, 0, 0, 0.5f } },
	{ 0, 1, 5, { 1, 1, 0, 0.5f } },
	
	{ 6, 1, 2, { 1, 1, 1, 0.5f } },
	{ 7, 2, 3, { 0, 0, 0.5f, 0.5f } },
	{ 7, 3, 8, { 0, 0.5f, 0, 0.5f } },
	{ 2, 7, 6, { 0, 0.5f, 0.5f, 0.5f } },
	{ 8, 4, 9, { 0.5f, 0, 0, 0.5f } },
	
	{ 8, 3, 4, { 0.5f, 0, 0.5f, 0.5f } },
	{ 9, 4, 5, { 0.5f, 0.5f, 0.5f, 0.5f } },
	{ 10, 1, 6, { 0, 0, 0.75f, 0.5f } },
	{ 5, 10, 9, { 0, 0.75f, 0, 0.5f } },
	{ 7, 11, 6, { 0, 0.75f, 0.75f, 0.5f } },
	
	{ 8, 11, 7, { 0.75f, 0, 0, 0.5f } },
	{ 8, 9, 11, { 0.75f, 0, 0.75f, 0.5f } },
	{ 10, 11, 9, { 0.75f, 0.75f, 0, 0.5f } },
	{ 6, 11, 10, { 0.75f, 0.75f, 0.75f, 0.5f } },
	{ 5, 1, 10, { 0.75f, 0.5f, 0.75f, 0.5f } }
};

float CalculateDistance(glm::vec3 pos1, glm::vec3 pos2)
{
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
}

void DrawSegment(const glm::vec3 point1, const glm::vec3 point2)
{
	glBegin(GL_LINE_STRIP);
	glVertex3d(point1.x, point1.y, point1.z);
	glVertex3d(point2.x, point2.y, point2.z);
	glEnd();
}

}

CIcosahedron::CIcosahedron() = default;

CIcosahedron::~CIcosahedron() = default;

void CIcosahedron::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIcosahedron::Draw() const
{
    for (const STriangleFace &face : ICOSAHEDRON_FACES)
    {
        const Vertex &v1 = ICOSAHEDRON_VERTICIES[face.vertexIndex1];
        const Vertex &v2 = ICOSAHEDRON_VERTICIES[face.vertexIndex2];
        const Vertex &v3 = ICOSAHEDRON_VERTICIES[face.vertexIndex3];
        glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		glColor4fv(glm::value_ptr(face.vertexColor));
		glBegin(GL_TRIANGLES);
        glNormal3fv(glm::value_ptr(normal));
        glVertex3fv(glm::value_ptr(v1));
        glVertex3fv(glm::value_ptr(v2));
        glVertex3fv(glm::value_ptr(v3));
		glEnd();
    }
}

void CIcosahedron::DrawEdges() const
{
	for (const STriangleFace &face : ICOSAHEDRON_FACES)
	{
		const Vertex &v1 = ICOSAHEDRON_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = ICOSAHEDRON_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = ICOSAHEDRON_VERTICIES[face.vertexIndex3];

		glLineWidth(3.f);
		glColor3f(0, 0, 0);
		DrawSegment(v1, v2);
		DrawSegment(v2, v3);
		DrawSegment(v1, v3);
	}
}
