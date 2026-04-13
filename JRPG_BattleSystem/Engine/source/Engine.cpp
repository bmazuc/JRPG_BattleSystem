#include "Engine.h"

WindowData::WindowData(const char* _title, int _width, int _height, SDL_WindowFlags _flags) 
    : title(_title), width(_width), height(_height), flags(_flags) 
{
}

void Engine::Start(WindowData windowData)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }

    // Setup one SDL Window
    window = SDL_CreateWindow(windowData.title, windowData.width, windowData.height, windowData.flags);

    if (!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return;
    }

    Run();
}

void Engine::Run()
{
    SDL_Event event;
    bool shouldExit = false;
    while (!shouldExit)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            shouldExit = true;
    }
}

void Engine::Shutdown()
{
    // Destroy any SDL objects we are allocated
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    // Quit SDL and shutdown systems we have initialized
    SDL_Quit();
}