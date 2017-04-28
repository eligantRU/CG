#pragma once

#include "libchapter3.h"
#include "IdentitySphere.h"
#include "KeyboardController.h"
#include "AudioController.h"
#include "Camera.h"
#include "Player.h"
#include "IdentityCube.h"
#include "Labyrinth.h"
#include "Skysphere.h"
#include "MoonProgramContext.h"
#include "BlockProgramContext.h"
#include "SkyProgramContext.h"
#include "FloorProgramContext.h"
#include "Rectangle.h"
#include "PhysWorld.h"

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
	bool m_lineMode = false;
	CPlayer m_player;
	
	CSkysphere m_skysphere;
	CSkyProgramContext m_skyContext;

	CPhysWorld m_physWorld;
	CSphereEntity m_sphere;
	CSphereEntity m_largeSphere;

	CSphereEntity m_moon;
	CMoonProgramContext m_moonContext;

	CCubeEntity m_floor;
	CFloorProgramContext m_floorContext;

	CLabyrinth m_labyrinth;

	CKeyboardController m_keyboardHandler;
	CAudioController m_audioController;

	CSound m_audio;
	std::vector<std::unique_ptr<CMusic>> m_trackList;
	unsigned m_volume = 5;
};
