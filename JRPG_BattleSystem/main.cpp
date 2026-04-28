// JRPG_BattleSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Core/Engine.h"
#include "BattleScene.h"
#include "MainMenuScene.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG

int main()
{
#ifdef _DEBUG
    // Allow memory leaks detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    Engine* engine = new Engine();

    if (engine->Start(WindowData("JRPG_BattleSystem", 640, 480, SDL_WINDOW_RESIZABLE)))
    {
        if (SceneManager* sceneManager = engine->GetSceneManager())
        {
            sceneManager->AddScene<BattleScene>("battleScene");
            sceneManager->AddScene<MainMenuScene>("mainMenu");
            sceneManager->SetActiveScene("mainMenu");
        }
        engine->Run();
    }

    engine->Shutdown();
    delete engine;
    engine = nullptr;

    return 0;
}
