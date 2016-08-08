#include "stdafx.h"
#include "Window.h"
#include "PhysicalWorld.h"
#include "consts.h"

namespace
{
glm::vec2 GetMousePosition(const SDL_MouseButtonEvent & event)
{
	return { event.x, event.y };
}
}

CWindow::CWindow()
	:m_world(new CPhysicalWorld(GRAVITY))
{
	SetBackgroundColor(BACKGROUND_COLOUR);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
    SetupView(size);
	m_world->Draw();
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
		m_world->Fire(GetMousePosition(event));
	}
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent & event)
{
	if (event.keysym.sym == SDLK_DELETE)
	{
		// TODO
	}
}
