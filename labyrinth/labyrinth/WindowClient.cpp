#include "stdafx.h"

#include "WindowClient.h"
#include "Renderer3D.h"
#include "Rectangle.h"

namespace
{

const glm::vec3 INITIAL_VIEW_DIRECTION = { 0, -1, 0 };
const glm::vec3 INITIAL_EYE_POSITION = { 0.5f, 8, 2 };
const glm::vec3 INITIAL_UP_DIRECTION = { 1, 0, 0 };

const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 GRAY_RGBA = { 0.5f, 0.5f, 0.5f, 1.f };

const auto AMBIENT_SCALE = 0.5f;
const auto MATERIAL_SHININESS = 50.f;
const glm::vec3 SUNLIGHT_DIRECTION = { -1, -1, -1 };

const auto SPHERE_ROTATION_SPEED = 0.2f;
const unsigned SPHERE_PRECISION = 40;

const auto MOVEMENT_SPEED = 0.03f;
const auto INTESITY_STEP = 0.05f;

const std::string MUSIC_PATH = "res/audio/music/";

const glm::vec3 MOON_POSITION = { 4, -1, 0 };
const auto MOON_MASS = 0.f;
const auto MOON_RADIUS = 1.f;
const glm::vec3 MOON_SIZE = { MOON_RADIUS, MOON_RADIUS, MOON_RADIUS };

const glm::vec3 FLOOR_POSITION = { -8.5f, 7.5f, 7.5f };
const auto FLOOR_MASS = 0.f;
const auto FLOOR_SIDE = 16.f;
const glm::vec3 FLOOR_SIZE = { FLOOR_SIDE, FLOOR_SIDE, FLOOR_SIDE };

const glm::vec3 SPHERE_POSITION = { 100, 1, 1 };
const auto SPHERE_MASS = 25.f;
const auto SPHERE_RADIUS = 1.f;
const glm::vec3 SPHERE_SIZE = { SPHERE_RADIUS, SPHERE_RADIUS, SPHERE_RADIUS };

const glm::vec3 LARGE_SPHERE_POSITION = { 150, 1, 1 };
const auto LARGE_SPHERE_MASS = 1'000'000.f;
const auto LARGE_SPHERE_RADIUS = 5.f;
const glm::vec3 LARGE_SPHERE_SIZE = { LARGE_SPHERE_RADIUS, LARGE_SPHERE_RADIUS, LARGE_SPHERE_RADIUS };

const int PHYS_PRECISION = 5;
const glm::vec3 GRAVITY = { -5, 0, 0 };

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
	// glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
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

template <class T, class TT>
void UpdateAndDraw(T & object, const glm::vec3 & size, CPhysWorld & world, TT & context, CRenderer3D & renderer)
{
	object.SetSizeScale(size);
	object.SetPosition(world.GetPosition(object.GetWorldIndex()));
	object.SetOrientation(world.GetOrientation(object.GetWorldIndex()));
	auto trans = object.ToMat4();
	DoWithTransform(context, trans, [&] {
		object.Draw(renderer);
	});
}

}

CWindowClient::CWindowClient(CWindow & window)
	:CAbstractWindowClient(window)
	,m_defaultVAO(CArrayObject::do_bind_tag())
	,m_sunlight(GL_LIGHT0)
	,m_camera(INITIAL_VIEW_DIRECTION, INITIAL_EYE_POSITION, INITIAL_UP_DIRECTION)
	,m_player(m_camera, m_keyboardHandler)
	,m_physWorld(GRAVITY)
	,m_floor(m_physWorld, 0.5f * FLOOR_SIDE, FLOOR_POSITION, FLOOR_MASS)
	,m_moon(m_physWorld, MOON_RADIUS, MOON_POSITION, MOON_MASS, SPHERE_PRECISION, SPHERE_PRECISION)
	,m_sphere(m_physWorld, SPHERE_RADIUS, SPHERE_POSITION, SPHERE_MASS, SPHERE_PRECISION, SPHERE_PRECISION)
	,m_largeSphere(m_physWorld, LARGE_SPHERE_RADIUS, LARGE_SPHERE_POSITION, LARGE_SPHERE_MASS, SPHERE_PRECISION, SPHERE_PRECISION)
	,m_labyrinth(m_physWorld)
	,m_audioController(CAudioController::GetInstance())
	,m_audio("res/audio/sound/push.wav")
	,m_musicPlayer(MUSIC_PATH)
{	
	GetWindow().SetBackgroundColor(BLACK_RGBA);
	CheckOpenGLVersion();
	SetupOpenGLState();

	auto * win = SDL_GL_GetCurrentWindow();
	auto windowSize = GetWindow().GetWindowSize();
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(win, windowSize.x / 2, windowSize.y / 2);

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(AMBIENT_SCALE * WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);

	m_camera.SetRotationFlag(true);

	m_musicPlayer.Play();
}

void CWindowClient::OnUpdateWindow(const float dt)
{
	m_musicPlayer.Update(dt);

	m_floorView.Update(dt);
	m_camera.Update(dt);
	m_skysphere.Update(dt);
	m_labyrinth.Update(dt);
	
	m_physWorld.StepSimulation(dt, PHYS_PRECISION);

	DispatchKeyboardEvent();

	SetupView(GetWindow().GetWindowSize());
	SetupLight0();

	CRenderer3D skyRenderer(m_skyContext);
	DoWithTransform(m_skyContext, glm::rotate(glm::radians(90.f), glm::vec3(0, 0, -1)),
	                              [&] {
		m_skysphere.Draw(skyRenderer);
	});

	CRenderer3D moonRenderer(m_moonContext);
	DoWithTransform(m_moonContext, glm::translate(m_physWorld.GetPosition(m_moon.GetWorldIndex()))
	                             * glm::rotate(glm::radians(90.f), glm::vec3(0, 0, 1)),
	                               [&] {
		m_moon.Draw(moonRenderer);
	});
	
	UpdateAndDraw(m_sphere, SPHERE_SIZE, m_physWorld, m_moonContext, moonRenderer);

	UpdateAndDraw(m_largeSphere, LARGE_SPHERE_SIZE, m_physWorld , m_moonContext, moonRenderer);

	CRenderer3D grassRenderer(m_floorContext);
	DoWithTransform(m_floorContext, glm::translate(glm::vec3(FLOOR_POSITION.x + 0.5f * FLOOR_SIZE.x, FLOOR_POSITION.y, FLOOR_POSITION.z))
	                              * glm::rotate(glm::radians(90.f), glm::vec3(0, 1, 0))
	                              * glm::scale(0.5f * FLOOR_SIZE),
	                                [&] {
		m_floorView.Draw(grassRenderer);
	});

	m_labyrinth.Draw();
}

void CWindowClient::OnDragBegin(const glm::vec2 & pos)
{
	(void)&pos;
}

void CWindowClient::OnDragMotion(const glm::vec2 & pos)
{
	if (m_camera.GetRotationFlag())
	{
		auto delta = pos - glm::vec2(GetWindow().GetWindowSize() / 2);
		m_camera.Rotate(delta);
	}
	auto * win = SDL_GL_GetCurrentWindow();
	SDL_WarpMouseInWindow(win, GetWindow().GetWindowSize().x / 2, GetWindow().GetWindowSize().y / 2);
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
		m_audioController.PlaySound(m_audio);
	}

	if (event.keysym.sym == SDLK_UP)
	{
		m_musicPlayer.TurnUpVolume();
	}
	if (event.keysym.sym == SDLK_DOWN)
	{
		m_musicPlayer.TurnDownVolume();
	}

	if (event.keysym.sym == SDLK_LEFT)
	{
		m_musicPlayer.PlayPrevTrack();
	}
	if (event.keysym.sym == SDLK_RIGHT)
	{
		m_musicPlayer.PlayNextTrack();
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

	m_floorContext.SetView(view);
	m_floorContext.SetProjection(proj);

	m_labyrinth.SetView(view);
	m_labyrinth.SetProjection(proj);
}

void CWindowClient::DispatchKeyboardEvent()
{
	auto speedFactor = 1.f;
	if (m_keyboardHandler.IsKeyPressed(SDLK_LSHIFT))
	{
		speedFactor *= 2;
	}

	glm::vec2 velocity = { 0, 0 };
	if (m_keyboardHandler.IsKeyPressed(SDLK_w))
	{
		velocity.x += MOVEMENT_SPEED;
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_s))
	{
		velocity.x -= MOVEMENT_SPEED;
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_a))
	{
		velocity.y += MOVEMENT_SPEED;
	}
	if (m_keyboardHandler.IsKeyPressed(SDLK_d))
	{
		velocity.y -= MOVEMENT_SPEED;
	}
	if (glm::length(velocity) > 0.f)
	{
		velocity = glm::normalize(velocity);
		m_camera.MoveFrontal(speedFactor * MOVEMENT_SPEED * velocity.x);
		m_camera.MoveHorizontal(speedFactor * MOVEMENT_SPEED * velocity.y);
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
	m_floorContext.SetLight0(light0);
	m_labyrinth.SetLight0(light0);
}
