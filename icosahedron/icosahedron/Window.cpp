#include "stdafx.h"
#include "Window.h"
#include "consts.h"

namespace
{

const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, 0.2f, 0.7f };
const float CAMERA_INITIAL_ROTATION = 0;
const float CAMERA_INITIAL_DISTANCE = 5.f;

void SetupOpenGLState()
{
    glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}

CWindow::CWindow()
    :m_camera(CAMERA_INITIAL_DISTANCE)
    ,m_sunlight(GL_LIGHT0)
{
    SetBackgroundColor(BACKGROUND_COLOUR);

	m_sunlight.SetPosition({ 2, 0 , 0 });
    m_sunlight.SetDiffuse(WHITE_RGBA);
    m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
    m_sunlight.SetSpecular(WHITE_RGBA);
}

void CWindow::OnWindowInit(const glm::ivec2 & size)
{
    (void)size;
    SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);
	m_sunlight.SetPosition(m_camera.GetPosition());
	m_icosahedron.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
    SetupView(size);
    m_sunlight.Setup();

	glPushMatrix();

	m_icosahedron.DrawEdges();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	m_icosahedron.Draw(); 
	glCullFace(GL_BACK);
	m_icosahedron.Draw();

    glPopMatrix();
}

void CWindow::SetupView(const glm::ivec2 & size)
{
    glViewport(0, 0, size.x, size.y);

    glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

    const float fieldOfView = glm::radians(70.f);
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
	m_camera.SetRotationFlag(true);
}

void CWindow::OnDragMotion(const glm::vec2 & pos)
{
	if (m_camera.GetRotationFlag())
	{
		static int x = 0;
		static int y = 0;

		if (x && y)
		{
			int alpha = pos.y - y;
			int beta = pos.x - x;
			const auto angle = m_camera.GetAngle();
			m_camera.SetAngle(std::pair<int, int>(angle.first + alpha, angle.second + beta));
		}

		x = pos.x;
		y = pos.y;
	}
}

void CWindow::OnDragEnd(const glm::vec2 & pos)
{
	m_camera.SetRotationFlag(false);
}
