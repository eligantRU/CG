#pragma once

#include "libchapter3.h"
#include "IRenderer3D.h"

class CShieldProgramContext;

class CShieldRenderer3D
	:public IRenderer3D
{
public:
	CShieldRenderer3D(CShieldProgramContext & context);
	~CShieldRenderer3D();

	void SetTexCoord2DOffset(size_t offset, size_t stride) override;
	void SetPosition3DOffset(size_t offset, size_t stride) override;
	void SetNormalOffset(size_t offset, size_t stride) override;

private:
	CShieldProgramContext & m_context;
	CVertexAttribute m_vertexAttr;
	CVertexAttribute m_normalAttr;
	CVertexAttribute m_texCoordAttr;
};