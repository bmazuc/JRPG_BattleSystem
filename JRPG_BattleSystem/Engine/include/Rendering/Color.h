#ifndef __COLOR_H_INCLUDED__
#define __COLOR_H_INCLUDED__

#include <glm/vec4.hpp>

using Color = glm::vec4;

namespace Colors
{
	constexpr Color White{ 1.0f, 1.0f, 1.0f, 1.0f };
	constexpr Color Grey{ 0.5f, 0.5f, 0.5f, 1.0f };
	constexpr Color Black{ 0.0f, 0.0f, 0.0f, 1.0f };
	constexpr Color Red{ 1.0f, 0.0f, 0.0f, 1.0f };
	constexpr Color Green{ 0.0f, 1.0f, 0.0f, 1.0f };
	constexpr Color Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
}

#endif