#include "stdafx.h"

#include "SkyRenderer3D.h"
#include "SkyProgramContext.h"

CSkyRenderer3D::CSkyRenderer3D(CSkyProgramContext & context)
	:m_context(context)
	,m_vertexAttr(m_context.GetPositionAttr())
	,m_normalAttr(m_context.GetNormalAttr())
	,m_texCoordAttr(m_context.GetTexCoordAttr())
{
	m_context.Use();
	m_vertexAttr.EnablePointer();
	m_normalAttr.EnablePointer();
	m_texCoordAttr.EnablePointer();
}

CSkyRenderer3D::~CSkyRenderer3D()
{
	m_vertexAttr.DisablePointer();
	m_normalAttr.DisablePointer();
	m_texCoordAttr.DisablePointer();
}

void CSkyRenderer3D::SetTexCoord2DOffset(size_t offset, size_t stride)
{
	m_texCoordAttr.SetVec2Offset(offset, stride);
}

void CSkyRenderer3D::SetPosition3DOffset(size_t offset, size_t stride)
{
	m_vertexAttr.SetVec3Offset(offset, stride, false);
}

void CSkyRenderer3D::SetNormalOffset(size_t offset, size_t stride)
{
	m_normalAttr.SetVec3Offset(offset, stride, false);
}
