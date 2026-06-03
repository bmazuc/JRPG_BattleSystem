#ifndef __ENEMY_SPAWNER_H_INCLUDED__
#define __ENEMY_SPAWNER_H_INCLUDED__

#include "BattleLevel/Spawners/CharacterSpawner.h"
#include "BattleLevel/Characters/Enemy.h"

class EnemySpawner : public CharacterSpawner
{
public:
	void SetGroupSize(unsigned int size) { groupSize = size; }

	std::vector<Enemy*> GenerateEnemies();

private:
	unsigned int groupSize = 3;
};

#endif // __ENEMY_SPAWNER_H_INCLUDED__