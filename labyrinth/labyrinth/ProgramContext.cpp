#include "stdafx.h"

#include "ProgramContext.h"

namespace
{

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CVertexAttribute CProgramContext::GetPositionAttr() const
{
	return m_program.FindAttribute("vertex");
}

CVertexAttribute CProgramContext::GetNormalAttr() const
{
	return m_program.FindAttribute("normal");
}

CVertexAttribute CProgramContext::GetTexCoordAttr() const
{
	return m_program.FindAttribute("textureUV");
}

const glm::mat4 & CProgramContext::GetModel() const
{
	return m_model;
}

const glm::mat4 & CProgramContext::GetView() const
{
	return m_view;
}

const glm::mat4 & CProgramContext::GetProjection() const
{
	return m_projection;
}

const SLightSource & CProgramContext::GetLight0() const
{
	return m_light0;
}

void CProgramContext::SetModel(const glm::mat4 & value)
{
	m_model = value;
}

void CProgramContext::SetView(const glm::mat4 & value)
{
	m_view = value;
}

void CProgramContext::SetProjection(const glm::mat4 & value)
{
	m_projection = value;
}

void CProgramContext::SetLight0(const SLightSource & source)
{
	m_light0 = source;
}
