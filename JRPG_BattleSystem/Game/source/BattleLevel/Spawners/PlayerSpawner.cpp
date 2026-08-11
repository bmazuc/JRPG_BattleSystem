#include "BattleLevel/Spawners/PlayerSpawner.h"
#include "World/Level/Scene/Scene.h"

std::vector<Character*> PlayerSpawner::GeneratePlayerGroup()
{
	std::vector<Character*> spawnedCharacters;

	spawnedCharacters.reserve(characterDatas.size());

	for (unsigned int idx = 0; idx < characterDatas.size(); idx++)
	{
		const CharacterData& data = characterDatas[idx];

		Character* character = GetScene()->SpawnActor<Character>(data.characterName, ActorSpawnInfo(), data);
		spawnedCharacters.push_back(character);
	}

	PositionCharacters(spawnedCharacters);

	return spawnedCharacters;
}