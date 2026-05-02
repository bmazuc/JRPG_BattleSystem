#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include "Scene/SceneManager.h"
#include "Core/Window.h"

#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>

#include <chrono>

class Renderer;
class InputManager;

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
	/*
	 *	Initialize the engine.
	 * 
	 *	@param config engine config parameters
	 *	@return true on success or false on failure
	 */
	bool Start(const EngineConfig& config);
	
	/*
	 *	Launch the engine main loop
	 */ 
	void Run();

	/*
	 *	Clean all resources, all objects created and stop engine
	 */
	void Shutdown();

	SceneManager* GetSceneManager() { return sceneManager; }
	const SceneManager* GetSceneManager() const { return sceneManager; }

private:
	/*
	 *	Initialize the SDL library
	 *	@return true on success or false on failure
	 */
	bool InitSDL();
	/*
	 *	Create a window wrapping and creating the sdl window.
	 *	@param config sdl window creation config parameters
	 *	@return true on success or false on failure
	 */
	bool CreateWindow(SDLWindowConfig config);
	/*
	 *	Initiliaze OpenGL + Glew + VSync (swapInterval)
	 *	@param swapInterval Swap interval for the current OpenGL context
	 *	@return true on success or false on failure
	 */
	bool InitOpenGL(int swapInterval);

	/*
	 *	Load the fallback resources
	 */ 
	void LoadDefaultResources();
	/*
	 *	Compute deltaTime between two frame.
	 *	Clamp to avoid spikes (when using breakpoints for example)debug, breakpoints, etc.)
	 *	@param lastTime time register at the previous frame.
	 *	@return computation result
	 */
	float ComputeDeltaTime(std::chrono::high_resolution_clock::time_point& lastTime);

	// Manage the different scenes (levels) of the game
	SceneManager* sceneManager;
	InputManager* inputManager;
	// Core rendering system base on OpenGL
	Renderer* renderer;
	// Wrapper for sdl window
	Window* window;

	/*
	 * Values used for clamping deltatime.
	 * From what I've looked into, these are the values used by Unreal.
	 */ 
	float minDeltaTime = 0.0005f;
	float maxDeltaTime = 0.40f;
};

#endif // __ENGINE_H_INCLUDED__