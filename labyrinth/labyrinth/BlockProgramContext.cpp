#include "stdafx.h"

#include "BlockProgramContext.h"

namespace
{

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CBlockProgramContext::CBlockProgramContext(const CTexture2DAtlas & atlas)
	:m_atlas(atlas)
{
	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/copytexture.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/copytexture.frag");
	m_program.CompileShader(vertShader, ShaderType::Vertex);
	m_program.CompileShader(fragShader, ShaderType::Fragment);
	m_program.Link();
}

void CBlockProgramContext::Use()
{
	glActiveTexture(GL_TEXTURE0);
	m_atlas.GetTexture().Bind();

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

CVertexAttribute CBlockProgramContext::GetPositionAttr() const
{
	return m_program.FindAttribute("vertex");
}

CVertexAttribute CBlockProgramContext::GetNormalAttr() const
{
	return m_program.FindAttribute("normal");
}

CVertexAttribute CBlockProgramContext::GetTexCoordAttr() const
{
	return m_program.FindAttribute("textureUV");
}

const glm::mat4 & CBlockProgramContext::GetModel() const
{
	return m_model;
}

const glm::mat4 & CBlockProgramContext::GetView() const
{
	return m_view;
}

const glm::mat4 & CBlockProgramContext::GetProjection() const
{
	return m_projection;
}

const CBlockProgramContext::SLightSource & CBlockProgramContext::GetLight0() const
{
	return m_light0;
}

void CBlockProgramContext::SetModel(const glm::mat4 & value)
{
	m_model = value;
}

void CBlockProgramContext::SetView(const glm::mat4 & value)
{
	m_view = value;
}

void CBlockProgramContext::SetProjection(const glm::mat4 & value)
{
	m_projection = value;
}

void CBlockProgramContext::SetLight0(const CBlockProgramContext::SLightSource & source)
{
	m_light0 = source;
}
