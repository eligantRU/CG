#include "stdafx.h"
#include "Window.h"

namespace
{

const glm::vec4 BACKGROUND_COLOUR = { 0, 0, 0, 1 };

const float POSITIVE_PARTICLE_ELECTRICAL_CHARGE = 1.f;
const float NEGATIVE_PARTICLE_ELECTRICAL_CHARGE = -1.f;

glm::vec2 GetMousePosition(const SDL_MouseButtonEvent & event)
{
	return { event.x, event.y };
}

}

CWindow::CWindow()
{
	auto pEmitter = std::make_unique<CParticleEmitter>();
	m_system.SetEmitter(std::move(pEmitter));
    SetBackgroundColor(BACKGROUND_COLOUR);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_time += deltaSeconds;
	m_system.Advance(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
    SetupView(size);
	m_system.Draw();
}

void CWindow::SetupView(const glm::ivec2 & size)
{
    const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnMouseDown(const SDL_MouseButtonEvent & event)
{
	OnDrop(event);
}

void CWindow::OnDrop(const SDL_MouseButtonEvent & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button == SDL_BUTTON_LEFT)
		{
			m_system.AddParticle(NEGATIVE_PARTICLE_ELECTRICAL_CHARGE, GetMousePosition(event));
		}
		else if (event.button == SDL_BUTTON_RIGHT)
		{
			m_system.AddParticle(POSITIVE_PARTICLE_ELECTRICAL_CHARGE, GetMousePosition(event));
		}
	}
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent & event)
{
	if (event.keysym.sym == SDLK_DELETE)
	{
		m_system.Clear();
	}
}
