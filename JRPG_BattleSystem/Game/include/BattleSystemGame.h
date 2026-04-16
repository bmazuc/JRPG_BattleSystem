#ifndef __BATTLE_SYSTEM_GAME_H_INCLUDED__
#define __BATTLE_SYSTEM_GAME_H_INCLUDED__

#include "Core/Game.h"

class GameObject;

class BattleSystemGame : public Game
{
public:
    void Init() override;
};

#endif // __BATTLE_SYSTEM_GAME_H_INCLUDED__