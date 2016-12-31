#pragma once

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <GL/glew.h>
#include <GL/gl.h>

#define GLM_FORCE_RADIANS
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_events.h>
#include <SDL_video.h>

// Did you install SDL_image development files?
// see http://www.libsdl.org/projects/SDL_image/
#include <SDL_image.h>

// Did you install SDL_ttf development files?
// see http://www.libsdl.org/projects/SDL_ttf/
#include <SDL_ttf.h>


#include <stdint.h>
#include <chrono>
#include <type_traits>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <vector>
