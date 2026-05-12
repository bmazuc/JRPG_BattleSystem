#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__

#include "SDL3/SDL.h"
#include <glm/vec2.hpp>

/**
 * Parameters used during SDL window creation.
 */
struct SDLWindowConfig
{
public:
	SDLWindowConfig() = default;
	SDLWindowConfig(const char* _title, glm::vec2 _resolution, SDL_WindowFlags _flags);
	
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

/**
 * Wrapper around an SDL window and OpenGL context.
 */
class Window
{
public:
	/**
	 * Creates the SDL window.
	 * @param config Window creation configuration.
	 * @return True on success, false otherwise.
	 */
	bool CreateSDLWindow(const SDLWindowConfig& config);

	/**
	 * Creates and activates the OpenGL context.
	 * Also configures the swap interval (VSync).
	 * @param swapInterval OpenGL swap interval.
	 * @return True on success, false otherwise.
	 */
	bool CreateOpenGLContext(int swapInterval);

	~Window();

	/**
	 * Swaps the front and back rendering buffers.
	 */
	bool SwapBuffers();

	/**
	 * Resizes the window.
	 */
	void Resize(glm::vec2 size);

	SDL_Window* GetSDLWindow() { return window; }
	const SDL_Window* GetSDLWindow() const { return window; }
	
	/**
	 * Returns the initial viewport resolution.
	 */
	glm::vec2 GetViewportBaseResolution() const { return viewportBaseResolution; }
	
	/**
	 * Returns the current window size.
	 */
	glm::vec2 GetSize() const;

private: 
	SDL_Window* window = nullptr;

	SDL_GLContext glContext = nullptr;

	// Initial resolution used for viewport calculations.
	glm::vec2 viewportBaseResolution;
};

#endif // __WINDOW_H_INCLUDED__