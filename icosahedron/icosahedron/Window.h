#pragma once

#include "stdafx.h"
#include "DispatchEvent.h"
#include "Bodies.h"
#include "Camera.h"
#include "Lights.h"

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
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;
	void OnScroll(const int &) override;

private:
    void SetupView(const glm::ivec2 &size);

	CIcosahedron m_icosahedron;
    CCamera m_camera;
    CDirectedLightSource m_sunlight;
};
