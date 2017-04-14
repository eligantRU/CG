#include "stdafx.h"

#include "Skysphere.h"
#include "IdentitySphere.h"

namespace
{

const float ROTATION_PERIOD_SEC = 1000.f;
const unsigned SPHERE_PRECISION = 50;

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
