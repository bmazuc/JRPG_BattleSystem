#ifndef __BATTLE_SYSTEM_GAME_H_INCLUDED__
#define __BATTLE_SYSTEM_GAME_H_INCLUDED__

#include "Game.h"

class Sprite;

class BattleSystemGame :
    public Game
{
public:
    ~BattleSystemGame();

    void Init(SpriteRenderer* renderer) override;
    void Update() override;

private:
    // Temp
    Sprite* sprite;
    Sprite* sprite2;
};

#endif // __BATTLE_SYSTEM_GAME_H_INCLUDED__