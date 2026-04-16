// JRPG_BattleSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Core/Engine.h"
#include "BattleSystemGame.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG

int main()
{
#ifdef _DEBUG
    // Allow memory leaks detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    WindowData windowData("JRPG_BattleSystem", 640, 480, SDL_WINDOW_RESIZABLE);

    BattleSystemGame* game = new BattleSystemGame();

    Engine* engine = new Engine();
    engine->Start(windowData, game);
    engine->Shutdown();

    delete game;
    game = nullptr;

    delete engine;
    engine = nullptr;

    return 0;
}
