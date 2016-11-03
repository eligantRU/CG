#pragma once

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <Windows.h>
#endif

#pragma warning(push, 3)

#include <GL/gl.h>

#define GLM_FORCE_RADIANS
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL_events.h>

#include <boost/noncopyable.hpp>

#pragma warning(pop)

#include <chrono>
#include <type_traits>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <vector>
#include <stdint.h>
