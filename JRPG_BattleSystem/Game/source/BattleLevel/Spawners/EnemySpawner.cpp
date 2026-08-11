#include "BattleLevel/Spawners/EnemySpawner.h"
#include "Core/Random.h"
#include "World/Level/Scene/Scene.h"

std::vector<Enemy*> EnemySpawner::GenerateEnemies()
{
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Character*> charactersToPosition;

	spawnedEnemies.reserve(groupSize);
	charactersToPosition.reserve(groupSize);

	for (unsigned int idx = 0; idx < groupSize; idx++)
	{
		const CharacterData& data = characterDatas.size() > 0 ?
			characterDatas[Random::FromRange(0, (int)characterDatas.size() - 1)] :
			CharacterData();

		Enemy* enemy = GetScene()->SpawnActor<Enemy>(data.characterName, ActorSpawnInfo(), data);
		spawnedEnemies.push_back(enemy);
		charactersToPosition.push_back(enemy);
	}

	PositionCharacters(charactersToPosition);

	return spawnedEnemies;
}
