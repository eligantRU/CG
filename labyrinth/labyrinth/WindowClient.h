#pragma once

#include "libchapter3.h"
#include "IdentitySphere.h"
#include "KeyboardController.h"
#include "Camera.h"
#include "Player.h"
#include "Cube.h"
#include "Labyrinth.h"
#include "Skysphere.h"
#include "MoonProgramContext.h"
#include "BlockProgramContext.h"
#include "SkyProgramContext.h"
#include "FloorProgramContext.h"
#include "Blocks.h"
#include "Rectangle.h"

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
	CLabyrinth m_labyrinth;
	CPlayer m_player;
	
	CSkysphere m_skysphere;
	CSkyProgramContext m_skyContext;

	CIdentitySphere m_moon;
	CMoonProgramContext m_moonContext;

	CRectangle m_grass;
	CFloorProgramContext m_grassContext;

	CKeyboardController m_keyboardHandler;
};
