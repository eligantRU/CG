#include "stdafx.h"

#include "WindowClient.h"

namespace
{

const glm::vec2 QUAD_TOPLEFT = { -300, -300 };
const glm::vec2 QUAD_SIZE = { 600, 600 };

const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec4 RED_RGBA = { 1, 0, 0, 1 };
const glm::vec4 GREEN_RGBA = { 0, 1, 0, 1 };

const glm::vec2 RING_CENTER = { 2, 2 };
const float RING_BORDER = 0.01f;
const float RING_RADIUS = 0.5f;

const glm::vec2 CIRCLE_CENTER = { 2, 2 };
const float CIRCLE_RADIUS = 0.5f;

const glm::vec2 CANNABOLA_CENTER = { 2, 1.5 };

void SetupOpenGLState()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

void SetShaders(CShaderProgram & program,
                const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	const std::string vertexShader = CFilesystemUtils::LoadFileAsString(vertexShaderPath);
	const std::string fragmentShader = CFilesystemUtils::LoadFileAsString(fragmentShaderPath);
	program.CompileShader(vertexShader, ShaderType::Vertex);
	program.CompileShader(fragmentShader, ShaderType::Fragment);
	program.Link();
}

float GetWindowAspect(CWindow & window)
{
	auto size = glm::vec2(window.GetWindowSize());
	return (size.x / size.y);
}

}

CWindowClient::CWindowClient(CWindow & window)
	:CAbstractWindowClient(window)
	,m_quadObj(QUAD_TOPLEFT, QUAD_SIZE)
{
	GetWindow().SetBackgroundColor(BLACK_RGBA);
	CheckOpenGLVersion();
	SetupOpenGLState();

	SetShaders(m_programCircle, "res/circle.vert", "res/circle.frag");
	SetShaders(m_programRing, "res/ring.vert", "res/ring.frag");
	SetShaders(m_programSpiral, "res/spiral.vert", "res/spiral.frag");
	SetShaders(m_programCannabola, "res/cannabola.vert", "res/cannabola.frag");

	m_programQueue = { &m_programCircle, &m_programRing, &m_programSpiral, &m_programCannabola };
}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
	SetupView(GetWindow().GetWindowSize());
	m_time += deltaSeconds;

	auto currentProgram = m_programQueue.front();
	currentProgram->Use();
	if (currentProgram == &m_programSpiral)
	{
		m_programSpiral.FindUniform("time") = m_time;
		m_programSpiral.FindUniform("resolution") = glm::vec2(GetWindow().GetWindowSize());
		m_programSpiral.FindUniform("aspect") = glm::vec2(GetWindowAspect(GetWindow()), 1);
	}
	else if (currentProgram == &m_programCircle)
	{
		m_programCircle.FindUniform("center") = CIRCLE_CENTER;
		m_programCircle.FindUniform("radius") = CIRCLE_RADIUS;
		m_programCircle.FindUniform("color") = RED_RGBA;
	}
	else if (currentProgram == &m_programRing)
	{
		m_programRing.FindUniform("center") = RING_CENTER;
		m_programRing.FindUniform("radius") = RING_RADIUS;
		m_programRing.FindUniform("border") = RING_BORDER;
		m_programRing.FindUniform("color") = RED_RGBA;
	}
	else if (currentProgram == &m_programCannabola)
	{
		m_programCannabola.FindUniform("center") = CANNABOLA_CENTER;
		m_programCannabola.FindUniform("color") = GREEN_RGBA;
	}
	m_quadObj.Draw();
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent & event)
{
	if (event.keysym.sym == SDLK_RIGHT)
	{
		std::rotate(m_programQueue.begin(), m_programQueue.begin() + 1, m_programQueue.end());
	}
	if (event.keysym.sym == SDLK_LEFT)
	{
		std::rotate(m_programQueue.rbegin(), m_programQueue.rbegin() + 1, m_programQueue.rend());
	}
}

void CWindowClient::CheckOpenGLVersion()
{
	if (!GLEW_VERSION_2_0)
	{
		throw std::runtime_error("Sorry, but OpenGL 3.2 is not available");
	}
}

void CWindowClient::SetupView(const glm::ivec2 & size)
{
	const float halfWidth = float(size.x) * 0.5f;
	const float halfHeight = float(size.y) * 0.5f;
	const glm::mat4 matrix = glm::ortho<float>(-halfWidth, halfWidth, -halfHeight, halfHeight);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}
