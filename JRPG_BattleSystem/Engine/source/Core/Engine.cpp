#include "Core/Engine.h"

#include "Core/Renderer.h"
#include "Scene/SceneManager.h"
#include "Core/ResourceManager.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <algorithm>

WindowData::WindowData(const char* _title, int _width, int _height, SDL_WindowFlags _flags) 
    : title(_title), width(_width), height(_height), flags(_flags) 
{
}

bool Engine::Start(WindowData windowData, int swapInterval)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    windowData.flags |= SDL_WINDOW_OPENGL;

    // Setup one SDL Window
    window = SDL_CreateWindow(windowData.title, windowData.width, windowData.height, windowData.flags);

    if (!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!SDL_GL_SetSwapInterval(1))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "VSync not supported: %s", SDL_GetError());
        return false;
    }

    // Initialisation de GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error glewInit: %s", glewGetErrorString(err));
        return false;
    }

    LoadDefaultResources();

    sceneManager = new SceneManager();

    renderer = new Renderer();
    renderer->Init("Shaders/sprite.vs", "Shaders/sprite.frag", viewportBaseResolution);

    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create OpenGL renderer");
        return false;
    }

    return true;
}

void Engine::Run()
{
    sceneManager->Init();

    std::chrono::steady_clock::time_point lastTime = std::chrono::high_resolution_clock::now();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_Event event;
    bool shouldExit = false;
    while (!shouldExit)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            shouldExit = true;
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            int w = event.window.data1;
            int h = event.window.data2;
            glViewport(0, 0, w, h);
        }

        float deltaTime = ComputeDeltaTime(lastTime);

        sceneManager->Update(deltaTime);

        if (Scene* scene = sceneManager->GetActiveScene())
        {
            renderer->RenderWorld(scene);
            renderer->RenderUI(scene, window);
        }

        SDL_GL_SwapWindow(window);

    }
}

void Engine::Shutdown()
{
    ResourceManager::Clear();

    delete sceneManager;
    sceneManager = nullptr;

    delete renderer;
    renderer = nullptr;

    // Destroy any SDL objects we are allocated
    if (glContext)
    {
        SDL_GL_DestroyContext(glContext);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

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