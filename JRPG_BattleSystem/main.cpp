// JRPG_BattleSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
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

    Engine* engine = new Engine();
    engine->Start(windowData);
    engine->Shutdown();

    delete engine;
    engine = nullptr;

    return 0;
}
