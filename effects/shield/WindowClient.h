#pragma once

#include "libchapter3.h"
#include "IdentitySphere.h"
#include "KeyboardHandler.h"
#include "Camera.h"
#include "ShieldProgramContext.h"

class CWindowClient 
	:public CAbstractWindowClient
{
public:
	CWindowClient(CWindow & window);

protected:
	void OnDragBegin(const glm::vec2 & pos);
	void OnDragMotion(const glm::vec2 & pos);
	void OnDragEnd(const glm::vec2 & pos);

	void OnUpdateWindow(const float dt) override;
	void OnKeyUp(const SDL_KeyboardEvent &) override;
	void OnKeyDown(const SDL_KeyboardEvent & event) override;

private:
	void CheckOpenGLVersion();
	void SetupView(const glm::ivec2 & size);
	void SetupLight0();

	void DispatchKeyboardEvent();

	CPositionLightSource m_sunlight;
	CCamera m_camera;
	CKeyboardHandler m_keyboardHandler;

	CArrayObject m_defaultVAO;

	CIdentitySphere m_sphereObj;
	CShieldProgramContext m_programContext;

	float m_time = 0;
	float m_intensity = 0.5f;
	bool m_lineMode = false;
	glm::vec2 m_dragPosition;
};
