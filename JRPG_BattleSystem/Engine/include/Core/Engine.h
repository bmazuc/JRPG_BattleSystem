#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include "SDLWindowConfig.h"
#include <chrono>

class Window;
class World;
class Renderer;
class InputManager;

/**
 * Configuration used during engine initialization.
 */
struct EngineConfig
{
public:
	EngineConfig() {}

	/**
	 * Window creation parameters.
	 */
	SDLWindowConfig windowConfig;

	/**
	 * OpenGL swap interval:
	 * 0  -> VSync disabled
	 * 1  -> VSync enabled
	 * -1 -> Adaptive VSync
	 */
	int swapInterval = 1;
};

/**
 * Core engine class responsible for:
 * - system initialization
 * - main loop execution
 * - rendering
 * - level management
 * - shutdown and cleanup
 */
class Engine
{
public:
	/**
	 * Initializes engine systems and resources.
	 *
	 * @param config Engine startup configuration.
	 * @return True on success, false otherwise.
	 */
	bool Start(const EngineConfig& config);
	
	/**
	 * Starts the main engine loop.
	 */
	void Run();

	/**
	 * Releases all engine resources and shuts down subsystems.
	 */
	void Shutdown();

	World* GetWorld() { return world; }
	const World* GetWorld() const { return world; }

private:
	/**
	 * Initializes the SDL library.
	 */
	bool InitSDL();

	/**
	 * Creates the application window.
	 */
	bool CreateWindow(const SDLWindowConfig& config);

	/**
	 * Initializes OpenGL, GLEW, and swap interval settings.
	 */
	bool InitOpenGL(int swapInterval);

	/**
	 * Loads fallback engine resources.
	 */
	void LoadDefaultResources();

	/**
	 * Computes frame delta time.
	 * Delta time is clamped to avoid large simulation jumps caused by breakpoints or frame stalls.
	 */
	float ComputeDeltaTime(std::chrono::high_resolution_clock::time_point& lastTime);

	// Manages level lifetime and transitions.
	World* world;

	// Handles player input state.
	InputManager* inputManager;

	// Core OpenGL rendering system.
	Renderer* renderer;

	// SDL window wrapper.
	Window* window;

	// Delta time clamp range used to stabilize simulation updates. Values are the one that seems to be used in UE.
	float minDeltaTime = 0.0005f;
	float maxDeltaTime = 0.40f;
};

#endif // __ENGINE_H_INCLUDED__