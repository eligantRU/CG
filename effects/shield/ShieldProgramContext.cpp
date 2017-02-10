#include "stdafx.h"

#include "ShieldProgramContext.h"

namespace
{

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CShieldProgramContext::CShieldProgramContext()
{
	CTexture2DLoader loader;

	m_pShieldTexture = loader.Load("res/shield.png");

	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/shield.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/shield.frag");
	m_programShield.CompileShader(vertShader, ShaderType::Vertex);
	m_programShield.CompileShader(fragShader, ShaderType::Fragment);
	m_programShield.Link();
}

void CShieldProgramContext::Use()
{
	glActiveTexture(GL_TEXTURE0);
	m_pShieldTexture->Bind();

	m_programShield.Use();
	m_programShield.FindUniform("colormap") = 0;

	const glm::mat4 mv = m_view * m_model;
	m_programShield.FindUniform("view") = m_view;
	m_programShield.FindUniform("modelView") = mv;
	m_programShield.FindUniform("normalModelView") = GetNormalMatrix(mv);
	m_programShield.FindUniform("projection") = m_projection;
	m_programShield.FindUniform("intensity") = m_intensity;

	m_programShield.FindUniform("light0.position") = m_light0.position;
	m_programShield.FindUniform("light0.diffuse") = m_light0.diffuse;
	m_programShield.FindUniform("light0.specular") = m_light0.specular;
}

CVertexAttribute CShieldProgramContext::GetPositionAttr() const
{
	return m_programShield.FindAttribute("vertex");
}

CVertexAttribute CShieldProgramContext::GetNormalAttr() const
{
	return m_programShield.FindAttribute("normal");
}

CVertexAttribute CShieldProgramContext::GetTexCoordAttr() const
{
	return m_programShield.FindAttribute("textureUV");
}

const glm::mat4 & CShieldProgramContext::GetModel() const
{
	return m_model;
}

const glm::mat4 & CShieldProgramContext::GetView() const
{
	return m_view;
}

const glm::mat4 & CShieldProgramContext::GetProjection() const
{
	return m_projection;
}

const CShieldProgramContext::SLightSource & CShieldProgramContext::GetLight0() const
{
	return m_light0;
}

float CShieldProgramContext::GetIntensity() const
{
	return m_intensity;
}

void CShieldProgramContext::SetModel(const glm::mat4 & value)
{
	m_model = value;
}

void CShieldProgramContext::SetView(const glm::mat4 & value)
{
	m_view = value;
}

void CShieldProgramContext::SetProjection(const glm::mat4 & value)
{
	m_projection = value;
}

void CShieldProgramContext::SetLight0(const CShieldProgramContext::SLightSource & source)
{
	m_light0 = source;
}

void CShieldProgramContext::SetIntensity(const float intensity)
{
	m_intensity = intensity;
}
