#include "Core/Engine.h"

#include "Rendering/Renderer.h"
#include "Scene/SceneManager.h"
#include "Core/Resource/ResourceManager.h"
#include "Core/Inputs/InputManager.h"
#include "Core/Random.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <algorithm>

bool Engine::Start(const EngineConfig& config)
{
    if (InitSDL() 
        && CreateWindow(config.windowConfig) 
        && InitOpenGL(config.swapInterval))
    {
        LoadDefaultResources();
        Random::Init();
        sceneManager = new SceneManager();
        renderer = new Renderer();
        inputManager = new InputManager();
        return true;
    }

    return false;
}

void Engine::Run()
{
    sceneManager->Init();
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
   
        sceneManager->Update(deltaTime, inputManager);

        if (Scene* scene = sceneManager->GetActiveScene())
        {
            renderer->RenderWorld(scene, window->GetViewportBaseResolution());
            renderer->RenderUI(scene, window->GetSize());
        }

        window->SwapBuffers();
    }
}

void Engine::Shutdown()
{
    ResourceManager::Clear();

    delete inputManager;
    inputManager = nullptr;

    delete sceneManager;
    sceneManager = nullptr;

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

bool Engine::CreateWindow(SDLWindowConfig config)
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