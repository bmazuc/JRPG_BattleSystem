#include "Core/Window.h"

#include "SDL3/SDL_opengl.h"

SDLWindowConfig::SDLWindowConfig(const char* _title, glm::vec2 _resolution, SDL_WindowFlags _flags)
	: title(_title), resolution(_resolution), flags(_flags)
{
}

bool Window::CreateSDLWindow(const SDLWindowConfig& config)
{
	SDL_WindowFlags flags = config.flags;
	flags |= SDL_WINDOW_OPENGL;

	// Setup one SDL Window
	window = SDL_CreateWindow(config.title, (int)config.resolution.x, (int)config.resolution.y, flags);

	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return false;
	}

	viewportBaseResolution = config.resolution;

	return true;
}

bool Window::CreateOpenGLContext(int swapInterval)
{
	glContext = SDL_GL_CreateContext(window);
	if (!SDL_GL_SetSwapInterval(swapInterval))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "VSync not supported: %s", SDL_GetError());
		return false;
	}

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
	if (glContext)
	{
		SDL_GL_DestroyContext(glContext);
	}

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

void Window::Resize(glm::vec2 size)
{
	glViewport(0, 0, (int)size.x, (int)size.y);
}