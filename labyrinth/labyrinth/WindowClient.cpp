#include "stdafx.h"

#include "WindowClient.h"
#include "Renderer3D.h"
#include "Rectangle.h"

namespace
{

const glm::vec3 INITIAL_VIEW_DIRECTION = { 0, -1, 0 };
const glm::vec3 INITIAL_EYE_POSITION = { 0, 8, 2 };
const glm::vec3 INITIAL_UP_DIRECTION = { 1, 0, 0 };

const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 GRAY_RGBA = { 0.5f, 0.5f, 0.5f, 1.f };

const float AMBIENT_SCALE = 0.5f;
const float MATERIAL_SHININESS = 50.f;
const glm::vec3 SUNLIGHT_DIRECTION = { -1, -1, -1 };

const float SPHERE_ROTATION_SPEED = 0.2f;
const unsigned SPHERE_PRECISION = 40;

const float MOVEMENT_SPEED = 0.03f;
const float INTESITY_STEP = 0.05f;

const std::string MUSIC_PATH = "res/audio/music/";
const std::string MUSIC_EXTENSION = ".ogg";

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
void DoWithTransform(IProgramContext & context, const glm::mat4 & mat, T && callback)
{
	const auto was = context.GetView();
	context.SetView(was * mat);
	context.Use();
	callback();
	context.SetView(was);
}

std::vector<std::string> FindFilesByExtension(const std::string & root, const std::string & extension)
{
	std::vector<std::string> result;
	// boost::filesystem::recursive_directory_iterator for recursive search
	for (boost::filesystem::directory_iterator it(root), end; it != end; ++it)
	{
		if (it->path().extension() == extension)
		{
			std::ostringstream stream;
			stream << *it;
			auto path = stream.str();
			result.push_back(path.substr(1, path.length() - 2));
		}
	}
	return result;
}

}

CWindowClient::CWindowClient(CWindow & window)
	:CAbstractWindowClient(window)
	,m_defaultVAO(CArrayObject::do_bind_tag())
	,m_sunlight(GL_LIGHT0)
	,m_camera(INITIAL_VIEW_DIRECTION, INITIAL_EYE_POSITION, INITIAL_UP_DIRECTION)
	,m_player(m_camera, m_keyboardHandler)
	,m_moon(SPHERE_PRECISION, SPHERE_PRECISION)
	,m_grass(glm::vec2(-4, +4), glm::vec2(+4, -4))
	,m_audio("res/audio/noise/push.wav")
{
	GetWindow().SetBackgroundColor(BLACK_RGBA);
	CheckOpenGLVersion();
	SetupOpenGLState();

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(AMBIENT_SCALE * WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);

	m_camera.SetRotationFlag(true);

	const auto trackPaths = FindFilesByExtension(MUSIC_PATH, MUSIC_EXTENSION);
	for (const auto & trackPath : trackPaths)
	{
		m_trackList.push_back(std::make_unique<CMusic>(trackPath));
	}
	m_audioController.PlayMusic(*m_trackList.front());
	m_audioController.SetMusicVolume(m_volume);
	m_audioController.SetNoiseVolume(m_volume);
}

void CWindowClient::OnUpdateWindow(const float dt)
{
	if (m_audioController.IsPlayingMusic())
	{
		std::rotate(m_trackList.begin(), m_trackList.begin() + 1, m_trackList.end());
		m_audioController.PlayMusic(*m_trackList.front());
	}

	m_camera.Update(dt);
	m_skysphere.Update(dt);
	m_labyrinth.Update(dt);
	m_grass.Update(dt);
	
	DispatchKeyboardEvent();

	SetupView(GetWindow().GetWindowSize());
	SetupLight0();

	CRenderer3D skyRenderer(m_skyContext);

	DoWithTransform(m_skyContext, glm::rotate(glm::radians(90.f), glm::vec3(0, 0, -1)),
	                              [&] {
		m_skysphere.Draw(skyRenderer);
	});

	CRenderer3D moonRenderer(m_moonContext);
	DoWithTransform(m_moonContext, glm::translate(glm::vec3(2, 2, 2))
	                             * glm::rotate(glm::radians(90.f), glm::vec3(0, 0, 1)),
	                               [&] {
		m_moon.Draw(moonRenderer);
	});

	CRenderer3D grassRenderer(m_grassContext);
	DoWithTransform(m_grassContext, glm::translate(glm::vec3(-1, 0, 0))
	                              * glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(0, 1, 0))
	                              * glm::scale(glm::vec3(4, 4, 4)),
	                              [&]() {
		m_grass.Draw(grassRenderer);
	});

	m_labyrinth.Draw();
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
		SetupLineMode(m_lineMode);
		m_audioController.PlayNoise(m_audio);
	}

	if (event.keysym.sym == SDLK_UP)
	{
		if ((0 <= m_volume) && (m_volume < 100))
		{
			m_audioController.SetNoiseVolume(++m_volume);
			m_audioController.SetMusicVolume(++m_volume);
		}
	}
	if (event.keysym.sym == SDLK_DOWN)
	{
		if ((0 < m_volume) && (m_volume <= 100))
		{
			m_audioController.SetNoiseVolume(--m_volume);
			m_audioController.SetMusicVolume(--m_volume);
		}
	}

	if (event.keysym.sym == SDLK_LEFT)
	{
		std::rotate(m_trackList.rbegin(), m_trackList.rbegin() + 1, m_trackList.rend());
		m_audioController.PlayMusic(*m_trackList.front());
	}
	if (event.keysym.sym == SDLK_RIGHT)
	{
		std::rotate(m_trackList.begin(), m_trackList.begin() + 1, m_trackList.end());
		m_audioController.PlayMusic(*m_trackList.front());
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
	const auto view = m_camera.GetViewTransform();
	const float fieldOfView = glm::radians(70.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;
	const auto proj = glm::perspective(fieldOfView, aspect, zNear, zFar);

	glViewport(0, 0, size.x, size.y);

	m_moonContext.SetView(view);
	m_moonContext.SetProjection(proj);

	auto skyView = view; // TODO: move to the function
	skyView[3][0] = 0;
	skyView[3][1] = 0;
	skyView[3][2] = 0;
	m_skyContext.SetView(skyView);
	m_skyContext.SetProjection(proj);

	m_grassContext.SetView(view);
	m_grassContext.SetProjection(proj);

	m_labyrinth.SetView(view);
	m_labyrinth.SetProjection(proj);
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

void CWindowClient::SetupLight0()
{
	SLightSource light0;
	light0.specular = m_sunlight.GetSpecular();
	light0.diffuse = m_sunlight.GetDiffuse();
	light0.position = m_sunlight.GetUniformPosition();
	m_moonContext.SetLight0(light0);
	m_skyContext.SetLight0(light0);
	m_grassContext.SetLight0(light0);
	m_labyrinth.SetLight0(light0);
}
