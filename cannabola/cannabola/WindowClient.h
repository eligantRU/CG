#pragma once

#include "libchapter3.h"
#include "Quad.h"

class CWindowClient 
	:public CAbstractWindowClient
{
public:
	CWindowClient(CWindow & window);

protected:
	void OnUpdateWindow(const float dt) override;
	void OnKeyUp(const SDL_KeyboardEvent &) override;
	
private:
	void CheckOpenGLVersion();
	void SetupView(const glm::ivec2 & size);
	
	CArrayObject m_defaultVAO;

	CQuad m_quadObj;
	CShaderProgram m_programSpiral;
	CShaderProgram m_programCircle;
	CShaderProgram m_programRing;
	CShaderProgram m_programCannabola;
	std::vector<CShaderProgram *> m_programQueue;

	float m_time = 0;
};
