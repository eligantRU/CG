#include "stdafx.h"

#include "Skysphere.h"
#include "IdentitySphere.h"

namespace
{

const char EARTH_TEX_PATH[] = "res/sky.jpg";
const float ROTATION_PERIOD_SEC = 1000.f;
const unsigned SPHERE_PRECISION = 50;

template<class T>
void DoAtCameraPosition(T && callback) // deprecated
{
	glm::mat4 modelView;
	glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelView));

	modelView[3][0] = 0;
	modelView[3][1] = 0;
	modelView[3][2] = 0;

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(modelView));
	callback();
	glPopMatrix();
}

glm::mat4 GetRotateZTransfrom(float phase)
{
	const float angle = float(2 * M_PI) * phase;
	return glm::rotate(glm::mat4(), angle, { 0, 0, 1 });
}

}

CSkysphere::CSkysphere()
	:m_sphere(SPHERE_PRECISION, SPHERE_PRECISION)
{
	glm::mat4 rotator = glm::rotate(glm::radians(-90.f), glm::vec3(-1, 0, 0));

	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_pSkyTexture = loader.Load(EARTH_TEX_PATH);
}

void CSkysphere::Update(const float dt)
{
	m_animationPhase += (dt / ROTATION_PERIOD_SEC);
	m_animationPhase = fmodf(m_animationPhase, 1.f);
}

void CSkysphere::Draw(IRenderer3D & renderer) const
{
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	glFrontFace(GL_CW);

	m_sphere.Draw(renderer);

	glFrontFace(GL_CCW);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
}
