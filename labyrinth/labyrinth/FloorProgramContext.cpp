#include "stdafx.h"

#include "FloorProgramContext.h"

namespace
{

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CFloorProgramContext::CFloorProgramContext()
{
	CTexture2DLoader loader;
	
	m_pTexture = loader.Load("res/floor/floor.jpg");
	m_pNormalTexture = loader.Load("res/floor/normal_floor.jpg");

	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/floor/floor.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/floor/floor.frag");
	m_program.CompileShader(vertShader, ShaderType::Vertex);
	m_program.CompileShader(fragShader, ShaderType::Fragment);
	m_program.Link();
}

void CFloorProgramContext::Use()
{
	glActiveTexture(GL_TEXTURE0);
	m_pTexture->Bind();

	glActiveTexture(GL_TEXTURE1);
	m_pNormalTexture->Bind();

	m_program.Use();
	m_program.FindUniform("colormap") = 0;
	m_program.FindUniform("normalmap") = 1;

	const glm::mat4 mv = m_view * m_model;
	m_program.FindUniform("view") = m_view;
	m_program.FindUniform("modelView") = mv;
	m_program.FindUniform("normalModelView") = GetNormalMatrix(mv);
	m_program.FindUniform("projection") = m_projection;

	m_program.FindUniform("light0.position") = m_light0.position;
	m_program.FindUniform("light0.diffuse") = m_light0.diffuse;
	m_program.FindUniform("light0.specular") = m_light0.specular;
}
