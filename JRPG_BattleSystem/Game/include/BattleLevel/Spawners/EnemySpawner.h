#ifndef __ENEMY_SPAWNER_H_INCLUDED__
#define __ENEMY_SPAWNER_H_INCLUDED__

#include "BattleLevel/Spawners/CharacterSpawner.h"
#include "BattleLevel/Characters/Enemy.h"

class EnemySpawner : public CharacterSpawner
{
public:
	~EnemySpawner();

	void AddCharacterData(CharacterData data) { characterDatas.push_back(data); }
	void SetGroupSize(unsigned int size) { groupSize = size; }

	std::vector<Enemy*> GenerateEnemies();

private:
	unsigned int groupSize = 3;

	std::vector<CharacterData> characterDatas;
};

#endif // __ENEMY_SPAWNER_H_INCLUDED__