#pragma once

#include "stdafx.h"
#include "IBody.h"

using Function2D = std::function<float(float, float)>;
using Function3D = std::function<glm::vec3(float, float)>;

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

class CDottedFunctionSurface final : public IBody
{
public:
    CDottedFunctionSurface(const Function2D & fn);

    void Tesselate(const glm::vec2 & rangeX, const glm::vec2 & rangeZ, float step);

    void Update(float) final {}
    void Draw() const final;

private:
    Function2D m_fn;
    std::vector<SVertexP3N> m_vertices;
};

class CSolidFunctionSurface final : public IBody
{
public:
	CSolidFunctionSurface(const Function2D & fn);
    CSolidFunctionSurface(const Function3D & fn);

    void Tesselate(const glm::vec2 & rangeX, const glm::vec2 & rangeZ, float step);

    void Update(float) final {}
    void Draw() const final;

private:
	void DrawFace() const;

	Function3D m_fn;
    std::vector<SVertexP3N> m_vertices;
    std::vector<uint32_t> m_indicies;
};
