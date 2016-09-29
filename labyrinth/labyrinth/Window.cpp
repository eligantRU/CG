#include "stdafx.h"
#include "Window.h"
#include "consts.h"

namespace
{

const glm::vec3 INITIAL_VIEW_DIRECTION = { 1, 1, 0 };
const glm::vec3 INITIAL_EYE_POSITION = { 0, 0, 0 };
const glm::vec3 INITIAL_UP_DIRECTION = { 0, 0, 1 };
const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec3 ORANGE = { 1, 0.6275f, 0 };
const glm::vec4 ORANGE_RGBA = { 1, 0.6275f, 0, 1 };
const float MATERIAL_SHININESS = 30.f;
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1 };
const glm::vec4 YELLOW_RGBA = { 1, 1, 0, 1 };
const glm::vec4 PERPLE_RGBA = { 0.7686f, 0, 0.6706f, 1 }; 
const glm::vec3 SUNLIGHT_DIRECTION = { -1, 0.2f, 0.7f };
const float CAMERA_INITIAL_DISTANCE = 0.1f;

void SetupOpenGLState()
{
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void SetupLineMode(const bool flag)
{
	if (flag)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

}

CWindow::CWindow()
	:m_camera(new CCamera(INITIAL_VIEW_DIRECTION, INITIAL_EYE_POSITION, INITIAL_UP_DIRECTION))
	,m_sunlight(GL_LIGHT0)
{
	SetBackgroundColor(BACKGROUND_COLOUR);

	m_material.SetAmbient(ORANGE_RGBA);
	m_material.SetDiffuse(ORANGE_RGBA);
	m_material.SetSpecular(BLACK_RGBA);
	m_material.SetShininess(MATERIAL_SHININESS);

	m_sunlight.SetPosition(m_camera->GetPosition());
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
	m_sunlight.SetSpecular(BLACK_RGBA);

	m_player.SetCamera(m_camera);
	m_camera->SetRotationFlag(true);
}

void CWindow::OnWindowInit(const glm::ivec2 & size)
{
    (void)size;
    SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_camera->Update(deltaSeconds);
	m_sunlight.SetPosition(m_camera->GetPosition());
	m_labyrinth.Update(deltaSeconds);

	SetupLineMode(m_lineMode);
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	m_sunlight.Setup();
	m_material.Setup();
	m_labyrinth.Draw();
}

void CWindow::SetupView(const glm::ivec2 & size)
{
    glViewport(0, 0, size.x, size.y);

    glLoadMatrixf(glm::value_ptr(m_camera->GetViewTransform()));

	const float fieldOfView = glm::radians(60.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 100.f;
    const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnScroll(const int & zoom)
{
	m_camera->OnScale(zoom);
}

void CWindow::OnDragBegin(const glm::vec2 & pos)
{
	m_dragPosition = pos;
}

void CWindow::OnDragMotion(const glm::vec2 & pos)
{
	if (m_camera->GetRotationFlag())
	{
		auto lastPos = m_dragPosition;
		if (lastPos.x && lastPos.y)
		{
			m_camera->Rotate(pos - lastPos);
		}

		m_dragPosition = pos;
	}
}

void CWindow::OnDragEnd(const glm::vec2 & pos)
{
	(void)pos;
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent & key)
{
	auto pos = m_camera->GetPosition();
	m_player.DispatchKeyboardEvent(key);
	if (m_labyrinth.CheckCollision(m_player.GetPosition()))
	{
		m_camera->SetPosition(pos);
	}
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent & key)
{
	if (key.keysym.sym == SDLK_SPACE)
	{
		m_lineMode = !m_lineMode;
	}
	if (key.keysym.sym == SDLK_ESCAPE)
	{
		std::exit(0);
	}
}
