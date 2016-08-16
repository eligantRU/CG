#pragma once

#include "stdafx.h"
#include "DispatchEvent.h"
#include "PhysicalWorld.h"

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 & size) override;
	void OnMouseDown(const SDL_MouseButtonEvent & event) override;
	void OnDrop(const SDL_MouseButtonEvent & event);

private:
    void SetupView(const glm::ivec2 & size);

    float m_time = 0;
	std::shared_ptr<CWorld> m_world;
};
