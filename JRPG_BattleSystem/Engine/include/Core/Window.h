#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__

#include "SDL3/SDL.h"
#include <glm/vec2.hpp>

/*
 *	Contains SDL window creation parameters.
 */
struct SDLWindowConfig
{
public:
	SDLWindowConfig() {}
	SDLWindowConfig(const char* _title, glm::vec2 _resolution, SDL_WindowFlags _flags);
	
	// Window title
	const char* title = "";
	// Window resolution
	glm::vec2 resolution = glm::vec2(640.0f, 480.0f);
	/*
	 *	The flags put on the window at creation.
	 *	SDL_WINDOW_OPENGL is added at creation.
	 */
	SDL_WindowFlags flags = 0;
};

/*
 *	Wrapper for SDL window and OpenGL context.
 */
class Window
{
public:
	/*
	 *	Create a sdl window with the specified dimensions and flags.
	 *	@param config sdl window creation config parameters
	 *	@return true on success or false on failure
	 */
	bool CreateSDLWindow(SDLWindowConfig config);
	/*
	 *	Create an OpenGL context for an OpenGL window, and make it current.
	 *	Also set the vsync (swapInterval).
	 *	@param swapInterval Swap interval for the current OpenGL context
	 *	@return true on success or false on failure
	 */
	bool CreateOpenGLContext(int swapInterval);

	~Window();
	/*
	 *	Swap buffer to display the current contents of buffer on screen.
	 *	@return true on success or false on failure
	 */ 
	bool SwapBuffers();
	/*
	 *	Change the window size.
	 *	@param size the new size the window should be
	 */
	void Resize(glm::vec2 size);

	SDL_Window* GetSDLWindow() { return window; }
	const SDL_Window* GetSDLWindow() const { return window; }
	/*
	 *	@return the initial resolution set to the window
	 */
	glm::vec2 GetViewportBaseResolution() const { return viewportBaseResolution; }
	/*
	 *	@return the current resolution of the window
	 */
	glm::vec2 GetSize() const;

private: 
	SDL_Window* window = nullptr;
	SDL_GLContext glContext;

	// the initial resolution set to the window
	glm::vec2 viewportBaseResolution;
};

#endif // __WINDOW_H_INCLUDED__