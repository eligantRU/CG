#pragma once

#include "libchapter3.h"
#include "IRenderer3D.h"

class CBlockProgramContext;

class CBlockRenderer3D
	:public IRenderer3D
{
public:
	CBlockRenderer3D(CBlockProgramContext & context);
	~CBlockRenderer3D();

	void SetTexCoord2DOffset(size_t offset, size_t stride) override;
	void SetPosition3DOffset(size_t offset, size_t stride) override;
	void SetNormalOffset(size_t offset, size_t stride) override;

private:
	CBlockProgramContext & m_context;
	CVertexAttribute m_vertexAttr;
	CVertexAttribute m_normalAttr;
	CVertexAttribute m_texCoordAttr;
};
