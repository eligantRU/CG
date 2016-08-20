#include "stdafx.h"
#include "Window.h"
#include "consts.h"

namespace
{

const glm::vec4 BLACK = { 0, 0, 0, 1 };
const float MATERIAL_SHININESS = 30.f;
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1.f };
const glm::vec4 YELLOW_RGBA = { 1, 1, 0, 1 };
const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, 0.2f, 0.7f };
const float CAMERA_INITIAL_ROTATION = 0;
const float CAMERA_INITIAL_DISTANCE = 10.f;

void SetupOpenGLState()
{
    glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
}

float GetSinc(float x, float y)
{
	const float radius = std::hypotf(x, y);
	if (radius < std::numeric_limits<float>::epsilon())
	{
		return 1;
	}
	return sinf(radius) / radius;
}

float GetMonkeySaddle(float x, float y)
{
	return pow(x, 3) - 3 * x * pow(y, 2);
}

float GetHyperbolicParaboloid(float x, float y)
{
	const float a = 1.f;
	const float b = 1.f;
	return (pow(x, 2) / pow(a, 2) - pow(y, 2) / pow(b, 2)) / 2;
}

float GetEllipticalParaboloid(float x, float y)
{
	const float a = 1.f;
	const float b = 1.f;
	return (pow(x, 2) / pow(a, 2) + pow(y, 2) / pow(b, 2)) / 2;
}

}

CWindow::CWindow()
    :m_camera(CAMERA_INITIAL_DISTANCE)
	,m_surface(GetEllipticalParaboloid)
    ,m_sunlight(GL_LIGHT0)
{
    SetBackgroundColor(BACKGROUND_COLOUR);

	m_material.SetAmbient(YELLOW_RGBA);
	m_material.SetDiffuse(YELLOW_RGBA);
	m_material.SetSpecular(FADED_WHITE_RGBA);
	m_material.SetShininess(MATERIAL_SHININESS);

	m_surface.Tesselate({ -1, 1 }, { -1, 1 }, 0.05f);

	m_sunlight.SetPosition({ 10, 10 , 10 });
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
	m_surface.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	m_sunlight.Setup();
	m_material.Setup();
	//m_surface.Draw();

	/*glColor3f(0.0, 0.0, 0.0);
	GLfloat x, y, z = -20, angle;
	bool f = true;
	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle < 10; angle += 0.1, z += 0.5)
	{
		if (f) { glColor3f(1.0, 0.0, 0.0); f = false; }
		else { glColor3f(0.0, 0.0, 0.0); f = true; }
		x = 20 * cos(angle);
		y = 20 * sin(angle);
		glVertex3f(0, 0, z);
		glVertex3f(x, y, z);
	}
	glEnd();*/

	/*const float R = 10.f;
	const float r = 5.f;
	glBegin(GL_POINTS);
	for (float theta = 0; theta < 2 * M_PI; theta += 0.05f)
	{
		for (float phi = 0; phi < 2 * M_PI; phi += 0.05f)
		{
			float x = (R + r * cosf(phi)) * cosf(theta);
			float y = (R + r * cosf(phi)) * sinf(theta);
			float z = r * sinf(phi);
			glVertex3f(x, y, z);
		}
	}
	glEnd();*/

	/*const float h = 5.f;

	glBegin(GL_POINTS);
	for (float u = 0; u < 2 * M_PI; u += 0.05f)
	{
		for (float v = 0; v < 2 * M_PI; v += 0.05f)
		{
			float x = u * cosf(v);
			float y = u * sinf(v);
			float z = h * v;
			glVertex3f(x, y, z);
		}
	}
	glEnd();*/
	
	/*glBegin(GL_POINTS);
	for (float u = -2 * M_PI; u < 2 * M_PI; u += 0.02f)
	{
		for (float v = -2 * M_PI; v < 2 * M_PI; v += 0.02f)
		{
			float x = coshf(u) * cosf(v);
			float y = coshf(u) * sinf(v);
			float z = u;
			glVertex3f(x, y, z);
		}

	}
	glEnd();*/
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
	m_camera.SetRotationFlag(true);
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
	m_camera.SetRotationFlag(false);
}
