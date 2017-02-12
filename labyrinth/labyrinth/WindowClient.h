#pragma once

#include "libchapter3.h"
#include "IdentitySphere.h"
#include "KeyboardHandler.h"
#include "Camera.h"
#include "Player.h"
//#include "Labyrinth.h"
#include "Skysphere.h"
#include "MoonProgramContext.h"

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

	CArrayObject m_defaultVAO;

	CPhongModelMaterial m_material;
	CDirectedLightSource m_sunlight;
	CCamera m_camera;
	glm::vec2 m_dragPosition;
	bool m_lineMode = false;
	//std::unique_ptr<CLabyrinth> m_labyrinth;
	CPlayer m_player;
	CSkysphere m_pSkysphere;
	CTexture2DUniquePtr m_pEarthTexture;
	CIdentitySphere m_moon;
	CMoonProgramContext m_moonContext;

	CKeyboardHandler m_keyboardHandler;
};
