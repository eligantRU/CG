#include "stdafx.h"

#include "Window.h"
#include "IdentitySphere.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{

const glm::vec3 INITIAL_VIEW_DIRECTION = { -1, 0, 0 };
const glm::vec3 INITIAL_EYE_POSITION = { 8, 2, 0 };
const glm::vec3 INITIAL_UP_DIRECTION = { 0, 0, 1 };

const glm::vec4 BLACK = { 0, 0, 0, 1 };
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };

const float MATERIAL_SHININESS = 30.f;
const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1.f };
const glm::vec3 SUNLIGHT_DIRECTION = { 1, 1, 1 };

const char EARTH_TEX_PATH[] = "res/daily_earth.jpg";
const float EARTH_ROTATION_PERIOD_SEC = 12.f;
const unsigned SPHERE_PRECISION = 40;

void SetupOpenGLState()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
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
    :m_camera(INITIAL_VIEW_DIRECTION, INITIAL_EYE_POSITION, INITIAL_UP_DIRECTION)
    ,m_sunlight(GL_LIGHT0)
	,m_player(m_camera)
{
    SetBackgroundColor(BLACK);

	m_decoratedSphere.SetChild(std::make_unique<CIdentitySphere>(SPHERE_PRECISION, SPHERE_PRECISION, glm::vec3(0, 0, -18)));
	m_decoratedSphere.SetPeriod(EARTH_ROTATION_PERIOD_SEC);

	m_material.SetAmbient(WHITE_RGBA);
	m_material.SetDiffuse(WHITE_RGBA);
	m_material.SetSpecular(FADED_WHITE_RGBA);
	m_material.SetShininess(MATERIAL_SHININESS);

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);

	m_camera.SetRotationFlag(true);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
    (void)size;
    SetupOpenGLState();

	m_labyrinth = std::make_unique<CLabyrinth>();
	m_pSkysphere = std::make_unique<CSkysphere>();

    CTexture2DLoader loader;
    loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_pEarthTexture = loader.Load(EARTH_TEX_PATH);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_camera.Update(deltaSeconds);
	auto pos = m_camera.GetPosition();
	m_camera.SetPosition({ pos.x, pos.y, 0 });

	m_labyrinth->Update(deltaSeconds);
	m_decoratedSphere.Update(deltaSeconds);
	m_pSkysphere->Update(deltaSeconds);

	SetupLineMode(m_lineMode);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);

	m_sunlight.Setup();
	m_material.Setup();
	m_pSkysphere->Draw();
	m_labyrinth->Draw(); 
	m_pEarthTexture->DoWhileBinded([&] {
		m_decoratedSphere.Draw();
	});
}

void CWindow::SetupView(const glm::ivec2 & size)
{
	glViewport(0, 0, size.x, size.y);

	glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

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
	m_camera.OnScale(zoom);
}

void CWindow::OnDragBegin(const glm::vec2 & pos)
{
	m_dragPosition = pos;
}

void CWindow::OnDragMotion(const glm::vec2 & pos)
{
	if (m_camera.GetRotationFlag())
	{
		auto lastPos = m_dragPosition;
		if (lastPos.x && lastPos.y)
		{
			m_camera.Rotate(pos - lastPos);
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
	auto pos = m_camera.GetPosition();
	m_player.DispatchKeyboardEvent(key);
	if (m_labyrinth->CheckCollision(m_player.GetPosition()))
	{
		m_camera.SetPosition(pos);
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
