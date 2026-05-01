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
	
	const char* title = "";
	glm::vec2 resolution = glm::vec2(640.0f, 480.0f);
	SDL_WindowFlags flags = 0;
};

/*
 *	Wrapper for SDL window and OpenGL context.
 */
class Window
{
public:
	bool CreateSDLWindow(SDLWindowConfig config);
	bool CreateOpenGLContext(int swapInterval);

	~Window();
	// Swap buffer to display the current contents of buffer on screen
	bool SwapBuffers();
	void OnResize(int w, int h);

	SDL_Window* GetSDLWindow() const { return window; }
	glm::vec2 GetViewportBaseResolution() const{ return viewportBaseResolution; }
	glm::vec2 GetSize() const;

private: 
	SDL_Window* window = nullptr;
	SDL_GLContext glContext;

	glm::vec2 viewportBaseResolution;
};

#endif // __WINDOW_H_INCLUDED__