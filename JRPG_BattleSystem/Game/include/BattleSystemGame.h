#ifndef __BATTLE_SYSTEM_GAME_H_INCLUDED__
#define __BATTLE_SYSTEM_GAME_H_INCLUDED__

#include "Game.h"

class Sprite;

class BattleSystemGame : public Game
{
public:
    void Init() override;
    void Update() override;
};

#endif // __BATTLE_SYSTEM_GAME_H_INCLUDED__