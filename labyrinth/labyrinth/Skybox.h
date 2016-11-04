#pragma once

#include "Cube.h"
#include "libchapter2.h"

class CSkybox final 
	:public ISceneObject
{
public:
	CSkybox();
	void Update(float dt) final;
	void Draw()const final;

private:
	CCube m_cube;
	CTexture2DAtlas m_atlas;
};
