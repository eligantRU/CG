#include "stdafx.h"
#include "Window.h"
#include "consts.h"

namespace
{

const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec3 ORANGE = { 1, 0.6275f, 0 };
const glm::vec4 ORANGE_RGBA = { 1, 0.6275f, 0, 1 };
const float MATERIAL_SHININESS = 30.f;
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1 };
const glm::vec4 YELLOW_RGBA = { 1, 1, 0, 1 };
const glm::vec4 PERPLE_RGBA = { 0.7686f, 0, 0.6706f, 1 }; 
const glm::vec3 SUNLIGHT_DIRECTION = { -1, 0.2f, 0.7f };
const float CAMERA_INITIAL_DISTANCE = 10.f;

void SetupOpenGLState()
{
	glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);

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

glm::vec3 GetTorus(float alpha, float beta)
{
	const float R = 10.f;
	const float r = 5.f;
	
	float x = (R + r * cosf(alpha)) * cosf(beta);
	float y = (R + r * cosf(alpha)) * sinf(beta);
	float z = r * sinf(alpha);

	return { x, y, z };
}

glm::vec3 GetHelicoid(float u, float v)
{
	const float h = 5.f;

	float x = u * cosf(v);
	float y = u * sinf(v);
	float z = h * v;

	return { x, y, z };
}

glm::vec3 GetCatenoid(float u, float v)
{
	const float h = 5.f;

	float x = coshf(u) * cosf(v);
	float y = coshf(u) * sinf(v);
	float z = u;

	return { x, y, z };
}

glm::vec3 GetMobiusStrip(float u, float v)
{
	float x = (1 + v / 2 * cosf(u / 2)) * cosf(u);
	float y = (1 + v / 2 * cosf(u / 2)) * sinf(u);
	float z = v / 2 * sinf(u / 2);

	return { x, y, z };
}

glm::vec3 GetKleinBottle(float u, float v)
{
	const float r = 1.f;

	float x = 0;
	float y = 0;
	float z = 0;

	if ((u >= 0) && (u < M_PI * 1.025f))
	{
		x = 6 * cosf(u) * (1 + sinf(u)) + 4 * r * (1 - cosf(u) / 2) * cosf(u) * cosf(v);
		y = 16 * sinf(u) + 4 * r * (1 - cosf(u) / 2) * sinf(u) * cosf(v);
		z = 4 * r * (1 - cosf(u) / 2) * sinf(v);
	}
	else if ((u > M_PI * 1.025f) && (u <= 2 * M_PI * 1.025f))
	{
		x = 6 * cosf(u) * (1 + sinf(u)) - 4 * r * (1 - cosf(u) / 2) * cosf(v);
		y = 16 * sinf(u);
		z = 4 * r * (1 - cosf(u) / 2) * sinf(v);
	}

	return { x, y, z };
}

}

SFunctionInfo::SFunctionInfo(const Function2D & fn, const glm::vec2 & rangeX, const glm::vec2 & rangeY, const float & step)
	:m_rangeX(rangeX)
	,m_rangeY(rangeY)
	,m_step(step)
	,m_functionType(FunctionType::Function2D)
{
	m_fn = [=](float x, float z) {
		return glm::vec3(x, fn(x, z), z);
	};

}

SFunctionInfo::SFunctionInfo(const Function3D & fn, const glm::vec2 & rangeX, const glm::vec2 & rangeY, const float & step)
	:m_fn(fn)
	,m_rangeX(rangeX)
	,m_rangeY(rangeY)
	,m_step(step)
	,m_functionType(FunctionType::Function3D)
{

}

SFunctionInfo::~SFunctionInfo() = default;

Function3D SFunctionInfo::GetFunction() const
{
	return m_fn;
}

glm::vec2 SFunctionInfo::GetRangeX() const
{
	return m_rangeX;
}

glm::vec2 SFunctionInfo::GetRangeY() const
{
	return m_rangeY;
}

float SFunctionInfo::GetStep() const
{
	return m_step;
}

FunctionType SFunctionInfo::GetFunctionType() const
{
	return m_functionType;
}

CWindow::CWindow()
	:m_camera(CAMERA_INITIAL_DISTANCE)
	, m_sunlight(GL_LIGHT0)
{
	SetBackgroundColor(BACKGROUND_COLOUR);

	m_material.SetAmbient(ORANGE_RGBA);
	m_material.SetDiffuse(ORANGE_RGBA);
	m_material.SetSpecular(BLACK_RGBA);
	m_material.SetShininess(MATERIAL_SHININESS);

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
	m_sunlight.SetSpecular(BLACK_RGBA);

	m_functions = {
		SFunctionInfo(GetSinc, { -10, 10 }, { -10, 10 }, 0.1f),
		SFunctionInfo(GetHyperbolicParaboloid, { -2, 2 }, { -2, 2 }, 0.1f),
		SFunctionInfo(GetEllipticalParaboloid, { -2, 2 }, { -2, 2 }, 0.1f),
		SFunctionInfo(GetMonkeySaddle, { -1, 1 }, { -1, 1 }, 0.1f),
		SFunctionInfo(GetHelicoid, { -10, 10 }, { -4, 4 }, 0.1f),
		SFunctionInfo(GetCatenoid, { -1.5f, 1.5f }, { -M_PI * 1.025f, M_PI * 1.025f }, 0.1f),
		SFunctionInfo(GetMobiusStrip, { 0, 2 * M_PI * 1.025f }, { -1, 1 }, 0.1f),
		SFunctionInfo(GetKleinBottle,{ 0, 6.4f }, { 0, 2 * M_PI * 1.025f }, 0.1f),
		SFunctionInfo(GetTorus,{ 0, 2 * M_PI * 1.025f }, { 0, 7 }, 0.1f)
	};

	m_surface.SetFunction(m_functions[0].GetFunction(), m_functions[0].GetFunctionType());
	m_surface.Tesselate(m_functions[0].GetRangeX(), m_functions[0].GetRangeY(), m_functions[0].GetStep());
}

void CWindow::OnWindowInit(const glm::ivec2 & size)
{
    (void)size;
    SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);

	m_surface.Update(deltaSeconds);
	SetupLineMode(m_lineMode);
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	m_sunlight.Setup();
	m_material.Setup();
	m_surface.Draw();
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

void CWindow::OnKeyUp(const SDL_KeyboardEvent & key)
{
	if (key.keysym.sym == SDLK_SPACE)
	{
		m_lineMode = !m_lineMode;
	}
	if (key.keysym.sym == SDLK_RIGHT)
	{
		std::rotate(m_functions.begin(), m_functions.begin() + 1, m_functions.end());
		m_surface.SetFunction(m_functions[0].GetFunction(), m_functions[0].GetFunctionType());
		m_surface.Tesselate(m_functions[0].GetRangeX(), m_functions[0].GetRangeY(), m_functions[0].GetStep());
	}
	if (key.keysym.sym == SDLK_LEFT)
	{
		std::rotate(m_functions.rbegin(), m_functions.rbegin() + 1, m_functions.rend());
		m_surface.SetFunction(m_functions[0].GetFunction(), m_functions[0].GetFunctionType());
		m_surface.Tesselate(m_functions[0].GetRangeX(), m_functions[0].GetRangeY(), m_functions[0].GetStep());
	}
}
