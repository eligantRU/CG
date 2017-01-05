#include "stdafx.h"

#include "WindowClient.h"

namespace
{

const glm::vec3 INITIAL_VIEW_DIRECTION = { -1, 0, 0 };
const glm::vec3 INITIAL_EYE_POSITION = { 8, 2, 0 };
const glm::vec3 INITIAL_UP_DIRECTION = { 0, 0, 1 };

const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 GRAY_RGBA = { 0.5f, 0.5f, 0.5f, 1.f };

const float AMBIENT_SCALE = 0.5f;
const float MATERIAL_SHININESS = 50.f;
const glm::vec3 SUNLIGHT_DIRECTION = { -1, -1, -1 };

const float SPHERE_ROTATION_SPEED = 0.2f;
const unsigned SPHERE_PRECISION = 40;
const glm::vec3 SPHERE_POSITION = { 0, 0, 0 };
const std::string SHIELD_TEX_PATH = "res/shield2.png";

const float MOVEMENT_SPEED = 0.03f;
const float INTESITY_STEP = 0.05f;

void SetupOpenGLState()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

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

template <class T>
void DoWithTransform(const glm::mat4 & mat, T && callback)
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(mat));
	callback();
	glPopMatrix();
}

CTexture2DLoader MakeTextureLoader()
{
	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::REPEAT);
	return loader;
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

}

CWindowClient::CWindowClient(CWindow & window)
	:CAbstractWindowClient(window)
	,m_sunlight(GL_LIGHT0)
	,m_camera(INITIAL_VIEW_DIRECTION, INITIAL_EYE_POSITION, INITIAL_UP_DIRECTION)
{
	GetWindow().SetBackgroundColor(BLACK_RGBA);
	CheckOpenGLVersion();
	SetupOpenGLState();

	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(AMBIENT_SCALE * WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);
	m_sunlight.SetPosition(INITIAL_EYE_POSITION);

	m_material.SetShininess(MATERIAL_SHININESS);
	m_material.SetSpecular(WHITE_RGBA);
	m_material.SetDiffuse(GRAY_RGBA);
	m_material.SetAmbient(AMBIENT_SCALE * GRAY_RGBA);

	SetShaders(m_programShield, "res/shield.vert", "res/shield.frag");

	m_camera.SetRotationFlag(true);
	
	m_sphere.SetChild(std::make_unique<CIdentitySphere>(SPHERE_PRECISION, SPHERE_PRECISION, glm::vec3()));
	m_sphere.SetTransform(glm::rotate(glm::radians(-90.f), glm::vec3(-1, 0, 0)));
	m_pTexture = MakeTextureLoader().Load(SHIELD_TEX_PATH);
}

void CWindowClient::OnUpdateWindow(const float dt)
{
	m_time += dt;
	m_camera.Update(dt);
	UpdateRotation(dt);
	m_sphere.Update(dt);
	
	DispatchKeyboardEvent();

	SetupView(GetWindow().GetWindowSize());

	m_sunlight.Setup();
	m_material.Setup();

	m_programShield.Use();
	m_programShield.FindUniform("intensity") = m_intensity;
	DoWithTransform(m_sphereTranslateTransform, [&] {
		m_pTexture->DoWhileBinded([&] {
			DoWithTransform(glm::scale(glm::vec3(1, 1, 1)), [&] {
				glDepthMask(GL_FALSE);

				m_sphere.Draw();
				glFrontFace(GL_CW);
				m_sphere.Draw();
				glFrontFace(GL_CCW);

				glDepthMask(GL_TRUE);
			});
		});
	});
}

void CWindowClient::UpdateRotation(const float dt)
{
	const float deltaRotation = SPHERE_ROTATION_SPEED * dt;
	m_sphereRotateTransform = glm::rotate(m_sphereRotateTransform, deltaRotation, glm::vec3(0, 0, 1));
	m_sphereTranslateTransform = glm::translate(SPHERE_POSITION);
}

void CWindowClient::OnDragBegin(const glm::vec2 & pos)
{
	m_dragPosition = pos;
}

void CWindowClient::OnDragMotion(const glm::vec2 & pos)
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

void CWindowClient::OnDragEnd(const glm::vec2 & pos)
{
	(void)&pos;
}

void CWindowClient::OnKeyDown(const SDL_KeyboardEvent & event)
{
	m_keyboardHandler.OnKeyDown(event.keysym.sym);
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent & event)
{
	m_keyboardHandler.OnKeyUp(event.keysym.sym);
	if (event.keysym.sym == SDLK_TAB)
	{
		m_lineMode = !m_lineMode;
	}
	SetupLineMode(m_lineMode);

	if (event.keysym.sym == SDLK_UP)
	{
		if (m_intensity < 1.f)
		{
			m_intensity += INTESITY_STEP;
		}
	}
	if (event.keysym.sym == SDLK_DOWN)
	{
		if (m_intensity > 0.1f)
		{
			m_intensity -= INTESITY_STEP;
		}
	}

	if (event.keysym.sym == SDLK_ESCAPE)
	{
		std::exit(0);
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
	glViewport(0, 0, size.x, size.y);
	const glm::mat4 mv = m_camera.GetViewTransform();
	glLoadMatrixf(glm::value_ptr(mv));

	const float fieldOfView = glm::radians(70.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;
	const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
}

void CWindowClient::DispatchKeyboardEvent()
{
	auto k = 1.f;
	if (m_keyboardHandler.IsKeyPressed(SDLK_LSHIFT))
	{
		k *= 2;
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_w))
	{
		m_camera.MoveFrontal(k * MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_s))
	{
		m_camera.MoveFrontal(-k * MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_a))
	{
		m_camera.MoveHorizontal(k * MOVEMENT_SPEED);
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_d))
	{
		m_camera.MoveHorizontal(-k * MOVEMENT_SPEED);
	}
}
