// JRPG_BattleSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Core/Engine.h"
#include "World/World.h"
#include "MainMenu/MainMenuLevel.h"
#include "BattleLevel/BattleLevel.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

int main()
{
#ifdef _DEBUG
    // Allow memory leaks detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    EngineConfig config = EngineConfig();
    config.windowConfig = SDLWindowConfig("JRPG_BattleSystem", glm::vec2(640.0f, 480.0f), SDL_WINDOW_RESIZABLE);
    
    Engine* engine = new Engine();

    if (engine->Start(config))
    {
        if (World* world = engine->GetWorld())
        {
            world->AddLevel<MainMenuLevel>("mainMenu");
            world->AddLevel<BattleLevel>("battleLevel");
            world->SetDefaultLevel("mainMenu");
        }
        engine->Run();
    }

    engine->Shutdown();
    delete engine;
    engine = nullptr;

    return 0;
}
