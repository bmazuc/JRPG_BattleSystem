#include "BattleLevel/Characters/Enemy.h"
#include "BattleLevel/Abilities/AttackAbility.h"

Enemy::Enemy(CharacterData data)
    : Character(data)
{
    attackAbility = new AttackAbility();
    attackAbility->SetOwner(this);
}

void Enemy::BeginDestroy()
{
    Character::BeginDestroy();

    delete attackAbility;
    attackAbility = nullptr;
}