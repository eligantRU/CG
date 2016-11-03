#pragma once

#include "libchapter2.h"
#include "Lights.h"
#include "Skybox.h"
#include "Decorators.h"
#include <vector>
#include "Labyrinth.h"
#include "Camera.h"
#include "Player.h"
#include "Skysphere.h"

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnWindowInit(const glm::ivec2 &size) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

    // IInputEventAcceptor interface
	void OnScroll(const int &) override;
	void OnDragBegin(const glm::vec2 & pos) override;
	void OnDragMotion(const glm::vec2 & pos) override;
	void OnDragEnd(const glm::vec2 & pos) override;
	void OnKeyDown(const SDL_KeyboardEvent & key) override;
	void OnKeyUp(const SDL_KeyboardEvent & key) override;

private:
    void SetupView(const glm::ivec2 &size);

    CPhongModelMaterial m_material;
	CDirectedLightSource m_sunlight;
	CCamera m_camera;
	glm::vec2 m_dragPosition;
	bool m_lineMode = false;
	std::unique_ptr<CLabyrinth> m_labyrinth;
	CPlayer m_player;
	std::unique_ptr<CSkysphere> m_pSkysphere;
	CTexture2DUniquePtr m_pEarthTexture;
	CAnimatedDecorator m_decoratedSphere;
};
