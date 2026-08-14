#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "BattleLevel/Characters/Character.h"

class AttackAbility;

class Enemy : public Character
{
public:
	Enemy(CharacterData data);
	void BeginDestroy() override;

	AttackAbility* GetAttackAbility() { return attackAbility; }

private:
	AttackAbility* attackAbility;

	bool isAlive = true;
};

#endif // __ENEMY_H_INCLUDED__