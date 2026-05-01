#include "Core/Window.h"

#include "SDL3/SDL_opengl.h"

WindowData::WindowData(const char* _title, int _width, int _height, SDL_WindowFlags _flags)
	: title(_title), width(_width), height(_height), flags(_flags)
{
}

bool Window::CreateSDLWindow(WindowData data)
{
	data.flags |= SDL_WINDOW_OPENGL;

	// Setup one SDL Window
	window = SDL_CreateWindow(data.title, data.width, data.height, data.flags);

	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return false;
	}

	viewportBaseResolution = glm::vec2(data.width, data.height);

	return true;
}

glm::vec2 Window::GetSize() const
{
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	return glm::vec2(windowWidth, windowHeight);
}

Window::~Window()
{
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

bool Window::SwapBuffers()
{
	return SDL_GL_SwapWindow(window);
}

void Window::OnResize(int w, int h)
{
	glViewport(0, 0, w, h);
}