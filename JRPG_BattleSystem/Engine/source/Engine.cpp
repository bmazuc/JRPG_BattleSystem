#include "Engine.h"

#include "Texture.h"
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "Game.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

WindowData::WindowData(const char* _title, int _width, int _height, SDL_WindowFlags _flags) 
    : title(_title), width(_width), height(_height), flags(_flags) 
{
}

void Engine::Start(WindowData windowData, Game* _game, int swapInterval)
{
    game = _game;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }

    windowData.flags |= SDL_WINDOW_OPENGL;

    // Setup one SDL Window
    window = SDL_CreateWindow(windowData.title, windowData.width, windowData.height, windowData.flags);

    if (!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!SDL_GL_SetSwapInterval(1))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "VSync not supported: %s", SDL_GetError());
        return;
    }

    // Initialisation de GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error glewInit: %s", glewGetErrorString(err));
        return;
    }

    spriteRenderer = new SpriteRenderer();
    spriteRenderer->InitShader("Shaders/sprite.vs", "Shaders/sprite.frag");

    Run();
}

void Engine::Run()
{
    if (game)
    {
        game->Init(spriteRenderer);
    }

    spriteRenderer->InitRenderData(viewportBaseResolution);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer->Render(window);

        SDL_GL_SwapWindow(window);

        if (game)
        {
            game->Update();
        }
    }
}

void Engine::Shutdown()
{
    delete spriteRenderer;
    spriteRenderer = nullptr;

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