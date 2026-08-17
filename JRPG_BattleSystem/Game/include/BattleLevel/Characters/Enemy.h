#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "BattleLevel/Characters/Character.h"

class AttackAbility;

/**
 * Non-playable character controlled by the game.
 * Extends Character with enemy-specific combat abilities.
 */
class Enemy : public Character
{
public:
	Enemy(CharacterData data);
	void BeginDestroy() override;

	AttackAbility* GetAttackAbility() { return attackAbility; }

private:
	AttackAbility* attackAbility;
};

#endif // __ENEMY_H_INCLUDED__