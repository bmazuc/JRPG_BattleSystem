#ifndef __ENEMY_SPAWNER_H_INCLUDED__
#define __ENEMY_SPAWNER_H_INCLUDED__

#include "World/Actor.h"
#include "BattleLevel/Enemy.h"
#include <vector>

class EnemySpawner : public Actor
{
public:
	~EnemySpawner();

	void AddEnemyData(EnemyData data) { enemyDatas.push_back(data); }
	void SetGroupSize(unsigned int size) { groupSize = size; }
	void SetSpacing(float newSpacing) { spacing = newSpacing; }

	std::vector<Enemy*> GenerateEnemies();

private:
	void PositionEnemies(std::vector<Enemy*>& spawnedEnemies);

	unsigned int groupSize = 3;
	float spacing = 0;

	std::vector<EnemyData> enemyDatas;
};

#endif // __ENEMY_SPAWNER_H_INCLUDED__