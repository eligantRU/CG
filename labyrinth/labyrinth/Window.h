#pragma once

#include "stdafx.h"
#include "DispatchEvent.h"
#include "Camera.h"
#include "Lights.h"
#include "Labyrinth.h"
#include "Player.h"

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnWindowInit(const glm::ivec2 & size) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 & size) override;

    // IInputEventAcceptor interface
	void OnScroll(const int &) override;
	void OnDragBegin(const glm::vec2 & pos) override;
	void OnDragMotion(const glm::vec2 & pos) override;
	void OnDragEnd(const glm::vec2 & pos) override;
	void OnKeyDown(const SDL_KeyboardEvent & key) override;
	void OnKeyUp(const SDL_KeyboardEvent & key) override;

private:
    void SetupView(const glm::ivec2 & size);

	CPhongModelMaterial m_material;
    std::shared_ptr<CCamera> m_camera;
	CDirectedLightSource m_sunlight;
	glm::vec2 m_dragPosition;
	bool m_lineMode = false;
	CLabyrinth m_labyrinth;
	CPlayer m_player;
};
