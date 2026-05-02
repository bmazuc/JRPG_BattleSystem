// JRPG_BattleSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Core/Engine.h"
#include "BattleScene/BattleScene.h"
#include "MainMenu/MainMenuScene.h"

#ifdef _DEBUG
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
        if (SceneManager* sceneManager = engine->GetSceneManager())
        {
            sceneManager->AddScene<BattleScene>("battleScene");
            sceneManager->AddScene<MainMenuScene>("mainMenu");
            sceneManager->SetDefaultScene("mainMenu");
        }
        engine->Run();
    }

    engine->Shutdown();
    delete engine;
    engine = nullptr;

    return 0;
}
