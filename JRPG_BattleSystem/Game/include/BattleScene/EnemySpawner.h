#ifndef __ENEMY_SPAWNER_H_INCLUDED__
#define __ENEMY_SPAWNER_H_INCLUDED__

#include "Scene/Actor.h"
#include "BattleScene/Enemy.h"
#include <vector>

class EnemySpawner : public Actor
{
public:
	~EnemySpawner();

	void BeginPlay() override;

	void AddEnemyData(EnemyData data) { enemyDatas.push_back(data); }
	void SetGroupSize(unsigned int size) { groupSize = size; }
	void SetSpacing(float newSpacing) { spacing = newSpacing; }

private:
	void GenerateEnemies();
	void PositionEnemies();

	unsigned int groupSize = 3;
	float spacing = 0;

	std::vector<EnemyData> enemyDatas;
	std::vector<Enemy*> spawnedEnemies;
};

#endif // __ENEMY_SPAWNER_H_INCLUDED__