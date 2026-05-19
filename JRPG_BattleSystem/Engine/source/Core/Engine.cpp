#include "Core/Engine.h"

#include <GL/glew.h>

#include "Rendering/Renderer.h"
#include "World/World.h"
#include "Core/Window.h"
#include "Core/Resource/ResourceManager.h"
#include "Core/Inputs/InputManager.h"
#include "Core/Random.h"

#include <SDL3/SDL_opengl.h>
#include <algorithm>

bool Engine::Start(const EngineConfig& config)
{
    if (InitSDL() 
        && CreateWindow(config.windowConfig) 
        && InitOpenGL(config.swapInterval))
    {
        LoadDefaultResources();
        Random::Init();
        world = new World();
        renderer = new Renderer();
        inputManager = new InputManager();
        return true;
    }

    return false;
}

void Engine::Run()
{
    world->Init();
    renderer->Init();

    std::chrono::steady_clock::time_point lastTime = std::chrono::high_resolution_clock::now();

    while (!inputManager->IsQuitRequested())
    {
        inputManager->UpdateInputs();

        if (inputManager->IsWindowResized())
        {
            window->Resize(inputManager->GetWindowSize());
        }

        float deltaTime = ComputeDeltaTime(lastTime);
   
        world->Update(deltaTime, inputManager);
        renderer->RenderWorld(world, window->GetViewportBaseResolution(), window->GetSize());

        window->SwapBuffers();
    }
}

void Engine::Shutdown()
{
    ResourceManager::Clear();

    delete inputManager;
    inputManager = nullptr;

    delete world;
    world = nullptr;

    delete renderer;
    renderer = nullptr;

    delete window;
    window = nullptr;

    // Quit SDL and shutdown systems we have initialized
    SDL_Quit();
}

float Engine::ComputeDeltaTime(std::chrono::high_resolution_clock::time_point& lastTime)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = currentTime - lastTime;
    lastTime = currentTime;

    float deltaTime = delta.count();
    return std::clamp(deltaTime, minDeltaTime, maxDeltaTime);
}

void Engine::LoadDefaultResources()
{
    ResourceManager::LoadShader("Shaders/default.vs", "Shaders/default.frag", "default");
    ResourceManager::LoadShader("Shaders/text.vs", "Shaders/text.frag", "text");
    ResourceManager::LoadPNGTexture("Assets/missing.png", "default");
    ResourceManager::LoadFont("Assets/arial.ttf", 24, "default");
}

bool Engine::InitSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool Engine::CreateWindow(const SDLWindowConfig& config)
{
    // Setup one SDL Window
    window = new Window();
    return window->CreateSDLWindow(config);
}

bool Engine::InitOpenGL(int swapInterval)
{
    window->CreateOpenGLContext(swapInterval);

    // Initialisation de GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error glewInit: %s", glewGetErrorString(err));
        return false;
    }

    return true;
}