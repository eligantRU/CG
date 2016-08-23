#pragma once

#include "stdafx.h"
#include "DispatchEvent.h"
#include "ParticleSystem.h"

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 & size) override;
	void OnMouseDown(const SDL_MouseButtonEvent & event) override;
	void OnKeyDown(const SDL_KeyboardEvent &) override;
	void OnDrop(const SDL_MouseButtonEvent & event);

private:
    void SetupView(const glm::ivec2 & size);

	CParticleSystem m_system;
};
