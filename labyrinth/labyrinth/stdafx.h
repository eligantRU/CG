#pragma once

#include "targetver.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <chrono>
#include <limits>
#include <type_traits>
#include <iostream>
#include <mutex>
#include <memory>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <stdint.h>
#include <set>

#pragma warning (push, 3)

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glut.h>

#define GLM_FORCE_RADIANS
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/noncopyable.hpp>
#include <boost/variant.hpp>
#include <boost/scope_exit.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>

#pragma warning (pop)
