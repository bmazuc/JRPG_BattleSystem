#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

class SpriteRenderer;

// Allows to pass the data needed to create the SDL window when starting the engine
struct WindowData
{
	WindowData(const char* _title, int _width, int _height, SDL_WindowFlags _flags);
	const char* title;
	int width; 
	int height; 
	SDL_WindowFlags flags;
};

class Engine
{
public:
	/** 
	*		Start the engine and run it if all initialization complete successfully
	*		swapInterval : Set the swap interval for the current OpenGL context (0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync) 
	**/
	void Start(WindowData windowData, int swapInterval = 0);
	void Shutdown();

private:
	void Run();

	SpriteRenderer* spriteRenderer;
	SDL_Window* window;
	SDL_GLContext glContext;
};

#endif // __ENGINE_H_INCLUDED__