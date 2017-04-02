#include "stdafx.h"

#include "Cube.h"
#include "BlockProgramContext.h"

namespace
{

const char COBBLESTONE_TEXTURE_ATLAS[] = "res/cobblestone_block/cobblestone_block.plist";
const std::pair<CubeFace, const char *> COBBLESTONE_FRAME_MAPPING[] = {
	{ CubeFace::Front, "cobblestone_block_front.png" },
	{ CubeFace::Back, "cobblestone_block_back.png" },
	{ CubeFace::Top, "cobblestone_block_top.png" },
	{ CubeFace::Bottom, "cobblestone_block_bottom.png" },
	{ CubeFace::Left, "cobblestone_block_left.png" },
	{ CubeFace::Right, "cobblestone_block_right.png" }
};

CTexture2DLoader MakeTextureLoader()
{
	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::CLAMP_TO_EDGE);
	return loader;
}

glm::mat4 GetNormalMatrix(const glm::mat4 & modelView)
{
	return glm::transpose(glm::inverse(modelView));
}

}

CBlockProgramContext::CBlockProgramContext()
	:m_atlas(CFilesystemUtils::GetResourceAbspath(COBBLESTONE_TEXTURE_ATLAS), MakeTextureLoader())
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
