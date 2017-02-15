#pragma once

#include "libchapter3.h"
#include "IRenderer3D.h"

class CSkyProgramContext;

class CSkyRenderer3D // TODO: copy-paste class. Fix it
	:public IRenderer3D
{
public:
	CSkyRenderer3D(CSkyProgramContext & context);
	~CSkyRenderer3D();

	void SetTexCoord2DOffset(size_t offset, size_t stride) override;
	void SetPosition3DOffset(size_t offset, size_t stride) override;
	void SetNormalOffset(size_t offset, size_t stride) override;

private:
	CSkyProgramContext & m_context;
	CVertexAttribute m_vertexAttr;
	CVertexAttribute m_normalAttr;
	CVertexAttribute m_texCoordAttr;
};
