#ifndef __SDL_WINDOW_CONFIG_H_INCLUDED__
#define __SDL_WINDOW_CONFIG_H_INCLUDED__

#include "SDL3/SDL.h"
#include <glm/vec2.hpp>

/**
 * Parameters used during SDL window creation.
 */
struct SDLWindowConfig
{
public:
	SDLWindowConfig() = default;
	SDLWindowConfig(const char* _title, glm::vec2 _resolution, SDL_WindowFlags _flags) 
		: title(_title), resolution(_resolution), flags(_flags)
	{
	}

	// Window title
	const char* title = "";

	// Window resolution
	glm::vec2 resolution = glm::vec2(640.0f, 480.0f);

	/**
	 * SDL window creation flags.
	 * SDL_WINDOW_OPENGL is automatically added.
	 */
	SDL_WindowFlags flags = 0;
};

#endif // __SDL_WINDOW_CONFIG_H_INCLUDED__