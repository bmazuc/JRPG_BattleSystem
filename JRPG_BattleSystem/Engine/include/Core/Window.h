#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__

#include "SDL3/SDL.h"
#include <glm/vec2.hpp>

// Allows to pass the data needed to create the SDL window when starting the engine
struct WindowData
{
public:
	WindowData() {}
	WindowData(const char* _title, int _width, int _height, SDL_WindowFlags _flags);
	const char* title = "";
	int width = 640;
	int height = 480;
	SDL_WindowFlags flags;
};

class Window
{
public:
	bool CreateSDLWindow(WindowData data);

	~Window();
	// Swap buffer to display the current contents of buffer on screen
	bool SwapBuffers();
	void OnResize(int w, int h);

	SDL_Window* GetSDLWindow() const { return window; }
	glm::vec2 GetViewportBaseResolution() const{ return viewportBaseResolution; }
	glm::vec2 GetSize() const;

private: 
	SDL_Window* window = nullptr;

	glm::vec2 viewportBaseResolution;
};

#endif // __WINDOW_H_INCLUDED__