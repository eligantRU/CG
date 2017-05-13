#include "stdafx.h"

#include "IdentityCube.h"
#include "BlockProgramContext.h"

namespace
{

const char COBBLESTONE_TEXTURE_ATLAS[] = "res/brick_block/brick_block.plist";
const std::pair<CubeFace, const char *> COBBLESTONE_FRAME_MAPPING[] = {
	{ CubeFace::Front, "brick_block_front.png" },
	{ CubeFace::Back, "brick_block_back.png" },
	{ CubeFace::Top, "brick_block_top.png" },
	{ CubeFace::Bottom, "brick_block_bottom.png" },
	{ CubeFace::Left, "brick_block_left.png" },
	{ CubeFace::Right, "brick_block_right.png" }
};

const char COBBLESTONE_NORMAL_ATLAS[] = "res/brick_block/brick_normal.plist";
const std::pair<CubeFace, const char *> COBBLESTONE_NORMAL_MAPPING[] = {
	{ CubeFace::Front, "brick_normal_front.png" },
	{ CubeFace::Back, "brick_normal_back.png" },
	{ CubeFace::Top, "brick_normal_top.png" },
	{ CubeFace::Bottom, "brick_normal_bottom.png" },
	{ CubeFace::Left, "brick_normal_left.png" },
	{ CubeFace::Right, "brick_normal_right.png" }
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
	,m_normalAtlas(CFilesystemUtils::GetResourceAbspath(COBBLESTONE_NORMAL_ATLAS), MakeTextureLoader())
{
	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/brick_block/brick.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/brick_block/brick.frag");
	m_program.CompileShader(vertShader, ShaderType::Vertex);
	m_program.CompileShader(fragShader, ShaderType::Fragment);
	m_program.Link();
}

void CBlockProgramContext::Use()
{
	glActiveTexture(GL_TEXTURE0);
	m_atlas.GetTexture().Bind();
	
	glActiveTexture(GL_TEXTURE1);
	m_normalAtlas.GetTexture().Bind();
	
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

const CTexture2DAtlas & CBlockProgramContext::GetAtlas() const
{
	return m_atlas;
}
