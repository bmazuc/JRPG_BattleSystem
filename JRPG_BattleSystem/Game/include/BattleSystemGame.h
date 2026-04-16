#ifndef __BATTLE_SYSTEM_GAME_H_INCLUDED__
#define __BATTLE_SYSTEM_GAME_H_INCLUDED__

#include "Core/Game.h"

class GameObject;

class BattleSystemGame : public Game
{
public:
    void Init() override;
    void Update() override;

private:
    // Temp values for update test
    GameObject* enemy;
    float enemyMoveDirection = 1.0f;
    float enemySpeed = 3.0f;
};

#endif // __BATTLE_SYSTEM_GAME_H_INCLUDED__