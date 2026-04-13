#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <SDL3/SDL.h>

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
	Engine() = default;
	~Engine() = default;

	// Start the engine and run it if all initialization complete successfully
	void Start(WindowData windowData);
	void Shutdown();

private:
	void Run();

	SDL_Window* window;
};

#endif // __ENGINE_H_INCLUDED__