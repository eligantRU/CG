#pragma once

#include "stdafx.h"
#include "IBody.h"
#include "sheet.h"

using Function2D = std::function<float(float, float)>;
using Function3D = std::function<glm::vec3(float, float)>;

struct SVertexP3NT2
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;

	SVertexP3NT2() = default;
	SVertexP3NT2(const glm::vec3 & position, const glm::vec2 & uv)
		:position(position)
		,uv(uv)
	{

	}
};

class CSolidFunctionSurface final : public IBody
{
public:
	CSolidFunctionSurface(); 
	CSolidFunctionSurface(const Function2D & fn);
    CSolidFunctionSurface(const Function3D & fn);

    void Tesselate(const glm::vec2 & rangeX, const glm::vec2 & rangeZ, float step);

    void Update(float) final {}
    void Draw() const final;

	void SetFunction(const Function3D & fn, const FunctionType & type);

	void operator=(const Function3D & fn);

private:

	void DrawFace() const;

	Function3D m_fn;
    std::vector<SVertexP3NT2> m_vertices;
    std::vector<uint32_t> m_indicies;
	FunctionType m_functionType = FunctionType::Undefined;
};
