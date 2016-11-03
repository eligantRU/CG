#pragma once

#include "IdentitySphere.h"
#include "libchapter2.h"
#include "Decorators.h"
#include <boost/noncopyable.hpp>

class CSkysphere final : public ISceneObject
{
public:
	CSkysphere();
	void Update(float dt) final;
	void Draw() const final;

private:
	CTexture2DUniquePtr m_pSkyTexture;
	CTransformDecorator m_decoratedSphere;
	float m_animationPhase = 0;
};
