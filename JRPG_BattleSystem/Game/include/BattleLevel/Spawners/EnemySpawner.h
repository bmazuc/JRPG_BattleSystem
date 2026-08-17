#ifndef __ENEMY_SPAWNER_H_INCLUDED__
#define __ENEMY_SPAWNER_H_INCLUDED__

#include "BattleLevel/Spawners/CharacterSpawner.h"
#include "BattleLevel/Characters/Enemy.h"

/**
 * Spawner responsible for generating enemy groups.
 * Enemy characters are created from a configurable set of character data. When multiple character configurations are available, one is selected randomly for each spawned enemy.
 */
class EnemySpawner : public CharacterSpawner
{
public:
	~EnemySpawner();

	/**
	 * Adds a character configuration that can be used when spawning enemies.
	 */
	void AddCharacterData(CharacterData data) { characterDatas.push_back(data); }

	void SetGroupSize(unsigned int size) { groupSize = size; }

	/**
	 * Generates a list of enemies and positions them.
	 */
	std::vector<Enemy*> GenerateEnemies();

private:
	// Number of enemies generated
	unsigned int groupSize = 3;

	//  Character configurations available for enemy generation.
	std::vector<CharacterData> characterDatas;
};

#endif // __ENEMY_SPAWNER_H_INCLUDED__