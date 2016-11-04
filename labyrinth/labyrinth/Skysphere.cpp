#include "stdafx.h"

#include "Skysphere.h"
#include "IdentitySphere.h"

namespace
{

const char EARTH_TEX_PATH[] = "res/sky.jpg";
const float ROTATION_PERIOD_SEC = 1000.f;
const unsigned SPHERE_PRECISION = 50;

template<class T>
void DoAtCameraPosition(T && callback)
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

/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetRotateZTransfrom(float phase)
{
	// угол вращения вокруг оси Z лежит в отрезке [0...2*pi].
	const float angle = float(2 * M_PI) * phase;
	return glm::rotate(glm::mat4(), angle, { 0, 0, 1 });
}

}

CSkysphere::CSkysphere()
{
	m_decoratedSphere.SetChild(std::make_unique<CIdentitySphere>(SPHERE_PRECISION, SPHERE_PRECISION, glm::vec3(0, 0, 0)));
	
	glm::mat4 rotator = glm::rotate(glm::degrees(90.f), glm::vec3(-1, 0, 0));
	m_decoratedSphere.SetTransform(rotator);

	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_pSkyTexture = loader.Load(EARTH_TEX_PATH);
}

void CSkysphere::Update(float dt)
{
	m_decoratedSphere.Update(dt);

	m_animationPhase += (dt / ROTATION_PERIOD_SEC);
	m_animationPhase = fmodf(m_animationPhase, 1.f);
}

void CSkysphere::Draw() const
{
	const glm::mat4 matrix = GetRotateZTransfrom(m_animationPhase);
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(matrix));
	m_pSkyTexture->DoWhileBinded([&] {
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glFrontFace(GL_CW);
		DoAtCameraPosition([this] {
			m_decoratedSphere.Draw();
		});
		glFrontFace(GL_CCW);
		glDepthMask(GL_TRUE);
		glEnable(GL_LIGHTING);
	});
	glPopMatrix();	
}
