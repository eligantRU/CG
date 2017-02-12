#include "stdafx.h"

#include "BlockRenderer3D.h"
#include "BlockProgramContext.h"

CBlockRenderer3D::CBlockRenderer3D(CBlockProgramContext & context)
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

CBlockRenderer3D::~CBlockRenderer3D()
{
	m_vertexAttr.DisablePointer();
	m_normalAttr.DisablePointer();
	m_texCoordAttr.DisablePointer();
}

void CBlockRenderer3D::SetTexCoord2DOffset(size_t offset, size_t stride)
{
	m_texCoordAttr.SetVec2Offset(offset, stride);
}

void CBlockRenderer3D::SetPosition3DOffset(size_t offset, size_t stride)
{
	m_vertexAttr.SetVec3Offset(offset, stride, false);
}

void CBlockRenderer3D::SetNormalOffset(size_t offset, size_t stride)
{
	m_normalAttr.SetVec3Offset(offset, stride, false);
}
