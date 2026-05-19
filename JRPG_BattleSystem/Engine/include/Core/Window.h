#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__

#include "SDLWindowConfig.h"

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