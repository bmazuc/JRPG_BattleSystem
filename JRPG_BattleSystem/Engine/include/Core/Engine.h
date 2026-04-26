#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <glm/vec2.hpp>

class Scene;
class Renderer;

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
	*		swapInterval : Set the swap interval for the current OpenGL context (0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync) 
	**/
	bool Start(WindowData windowData, int swapInterval = 0);
	void Run();
	void Shutdown();

	template<typename T, typename... Args>
	void SetScene(Args&&... args)
	{
		static_assert(std::is_base_of<Scene, T>::value, "T must inherit Scene");

		scene = new T(std::forward<Args>(args)...);
	}

	void SetViewportBaseResolution(glm::vec2 resolution) { viewportBaseResolution = resolution; }

private:
	Scene* scene;
	Renderer* renderer;
	SDL_Window* window;
	SDL_GLContext glContext;

	glm::vec2 viewportBaseResolution = glm::vec2(640, 480);

	Uint64 lastTick = 0;
	Uint64 currentTick = 0;
};

#endif // __ENGINE_H_INCLUDED__