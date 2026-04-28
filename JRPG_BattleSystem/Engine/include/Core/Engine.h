#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include "Scene/SceneManager.h"

#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <glm/vec2.hpp>

#include <chrono>

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

	void SetViewportBaseResolution(glm::vec2 resolution) { viewportBaseResolution = resolution; }

	SceneManager* GetSceneManager() const { return sceneManager; }

private:
	void LoadDefaultResources();
	float ComputeDeltaTime(std::chrono::high_resolution_clock::time_point& lastTime);

	SceneManager* sceneManager;
	Renderer* renderer;
	SDL_Window* window;
	SDL_GLContext glContext;

	glm::vec2 viewportBaseResolution = glm::vec2(640, 480);

	/*
	 * Values used for clamping deltatime(avoid spike when using breakpoints for example.
	 * From what I've looked into, these are the values used by Unreal.
	 */ 
	float minDeltaTime = 0.0005f;
	float maxDeltaTime = 0.40f;
};

#endif // __ENGINE_H_INCLUDED__