#include "stdafx.h"

#include "SkyProgramContext.h"

namespace
{

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CSkyProgramContext::CSkyProgramContext()
{
	CTexture2DLoader loader;

	m_pTexture = loader.Load("res/sky.jpg");

	// NOTE: use another shaders
	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/copytexture.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/copytexture.frag");
	m_program.CompileShader(vertShader, ShaderType::Vertex);
	m_program.CompileShader(fragShader, ShaderType::Fragment);
	m_program.Link();
}

void CSkyProgramContext::Use()
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
