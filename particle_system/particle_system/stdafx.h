#pragma once

#include "targetver.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <type_traits>

#pragma warning (push, 3)

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glut.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/noncopyable.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>

#pragma warning (pop)
