#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include "Scene/SceneManager.h"
#include "Core/Window.h"

#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>

#include <chrono>

class Renderer;

/*
 *	Contains engine creation parameters.
 */
struct EngineConfig
{
public:
	EngineConfig() {}

	/*
	 *	Window creation parameter
	 */
	SDLWindowConfig windowConfig;
	/*
	 *	Swap interval for the current OpenGL context :
	 *	0	: immediate updates, 
	 *	1	: updates synchronized with the vertical retrace,
	 *	-1	: adaptive vsync
	 */
	int swapInterval = 1;
};

/*
 *	Core Engine class. 
 *	Manager global lifetime :
 *	- Initialisation (SDL, OpenGL, resources)
 *	- Main loop (events, update, render)
 *	- Shutdown
 *	Centralise core systems : Window, Renderer, SceneManager
 */
class Engine
{
public:
	/** 
	*		swapInterval : Set the swap interval for the current OpenGL context (0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync) 
	**/
	bool Start(const EngineConfig& config);
	void Run();
	void Shutdown();

	SceneManager* GetSceneManager() const { return sceneManager; }

private:
	bool InitSDL();
	bool CreateWindow(SDLWindowConfig config);
	bool InitOpenGL(int swapInterval);

	void LoadDefaultResources();
	float ComputeDeltaTime(std::chrono::high_resolution_clock::time_point& lastTime);

	SceneManager* sceneManager;
	Renderer* renderer;
	Window* window;

	/*
	 * Values used for clamping deltatime(avoid spike when using breakpoints for example.
	 * From what I've looked into, these are the values used by Unreal.
	 */ 
	float minDeltaTime = 0.0005f;
	float maxDeltaTime = 0.40f;
};

#endif // __ENGINE_H_INCLUDED__