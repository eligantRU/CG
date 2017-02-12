#include "stdafx.h"

#include "MoonProgramContext.h"

namespace
{

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CMoonProgramContext::CMoonProgramContext()
{
	CTexture2DLoader loader;

	m_pTexture = loader.Load("res/moon.jpg");

	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/copytexture.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/copytexture.frag");
	m_program.CompileShader(vertShader, ShaderType::Vertex);
	m_program.CompileShader(fragShader, ShaderType::Fragment);
	m_program.Link();
}

void CMoonProgramContext::Use()
{
	glActiveTexture(GL_TEXTURE0);
	m_pTexture->Bind();

	m_program.Use();
	m_program.FindUniform("colormap") = 0;

	const glm::mat4 mv = m_view * m_model;
	m_program.FindUniform("view") = m_view;
	m_program.FindUniform("modelView") = mv;
	m_program.FindUniform("normalModelView") = GetNormalMatrix(mv);
	m_program.FindUniform("projection") = m_projection;

	m_program.FindUniform("light0.position") = m_light0.position;
	m_program.FindUniform("light0.diffuse") = m_light0.diffuse;
	m_program.FindUniform("light0.specular") = m_light0.specular;
}

CVertexAttribute CMoonProgramContext::GetPositionAttr() const
{
	return m_program.FindAttribute("vertex");
}

CVertexAttribute CMoonProgramContext::GetNormalAttr() const
{
	return m_program.FindAttribute("normal");
}

CVertexAttribute CMoonProgramContext::GetTexCoordAttr() const
{
	return m_program.FindAttribute("textureUV");
}

const glm::mat4 & CMoonProgramContext::GetModel() const
{
	return m_model;
}

const glm::mat4 & CMoonProgramContext::GetView() const
{
	return m_view;
}

const glm::mat4 & CMoonProgramContext::GetProjection() const
{
	return m_projection;
}

const CMoonProgramContext::SLightSource & CMoonProgramContext::GetLight0() const
{
	return m_light0;
}

void CMoonProgramContext::SetModel(const glm::mat4 & value)
{
	m_model = value;
}

void CMoonProgramContext::SetView(const glm::mat4 & value)
{
	m_view = value;
}

void CMoonProgramContext::SetProjection(const glm::mat4 & value)
{
	m_projection = value;
}

void CMoonProgramContext::SetLight0(const CMoonProgramContext::SLightSource & source)
{
	m_light0 = source;
}
