#pragma once

#include "libchapter3.h"
#include "IRenderer3D.h"

class CMoonProgramContext;

class CMoonRenderer3D
	:public IRenderer3D
{
public:
	CMoonRenderer3D(CMoonProgramContext & context);
	~CMoonRenderer3D();

	void SetTexCoord2DOffset(size_t offset, size_t stride) override;
	void SetPosition3DOffset(size_t offset, size_t stride) override;
	void SetNormalOffset(size_t offset, size_t stride) override;

private:
	CMoonProgramContext & m_context;
	CVertexAttribute m_vertexAttr;
	CVertexAttribute m_normalAttr;
	CVertexAttribute m_texCoordAttr;
};
