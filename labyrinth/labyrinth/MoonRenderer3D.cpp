#include "stdafx.h"

#include "MoonRenderer3D.h"
#include "MoonProgramContext.h"

CMoonRenderer3D::CMoonRenderer3D(CMoonProgramContext & context)
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

CMoonRenderer3D::~CMoonRenderer3D()
{
	m_vertexAttr.DisablePointer();
	m_normalAttr.DisablePointer();
	m_texCoordAttr.DisablePointer();
}

void CMoonRenderer3D::SetTexCoord2DOffset(size_t offset, size_t stride)
{
	m_texCoordAttr.SetVec2Offset(offset, stride);
}

void CMoonRenderer3D::SetPosition3DOffset(size_t offset, size_t stride)
{
	m_vertexAttr.SetVec3Offset(offset, stride, false);
}

void CMoonRenderer3D::SetNormalOffset(size_t offset, size_t stride)
{
	m_normalAttr.SetVec3Offset(offset, stride, false);
}
