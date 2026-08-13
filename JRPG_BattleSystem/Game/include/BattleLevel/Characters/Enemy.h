#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "BattleLevel/Characters/Character.h"

class AttackAbility;

class Enemy : public Character
{
public:
	Enemy(CharacterData data);
	void BeginDestroy() override;

	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	AttackAbility* GetAttackAbility() { return attackAbility; }

	Delegate<void, Enemy*> OnSelected;

private:
	PlayerController* playerController;

	DelegateHandle clickHandle;

	AttackAbility* attackAbility;

	bool isAlive = true;
};

#endif // __ENEMY_H_INCLUDED__