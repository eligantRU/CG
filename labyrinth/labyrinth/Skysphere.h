#pragma once

#include "libchapter3.h"
#include "IdentitySphere.h"

class CSkysphere final
{
public:
	CSkysphere();
	void Update(const float dt);
	void Draw(IRenderer3D & renderer) const;

private:
	CIdentitySphere m_sphere;
	float m_animationPhase = 0;
};
