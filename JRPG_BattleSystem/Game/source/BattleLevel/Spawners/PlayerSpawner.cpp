#include "BattleLevel/Spawners/PlayerSpawner.h"
#include "World/Level/Scene/Scene.h"
#include "BattleLevel/Characters/PlayerCharacter.h"

PlayerSpawner::~PlayerSpawner()
{
	characterDatas.clear();
}

std::vector<PlayerCharacter*> PlayerSpawner::GeneratePlayerGroup()
{
	std::vector<PlayerCharacter*> spawnedCharacters;
	std::vector<Character*> charactersToPosition;

	spawnedCharacters.reserve(characterDatas.size());
	charactersToPosition.reserve(characterDatas.size());

	for (unsigned int idx = 0; idx < characterDatas.size(); idx++)
	{
		const PlayerCharacterData& data = characterDatas[idx];

		PlayerCharacter* character = GetScene()->SpawnActor<PlayerCharacter>(data.characterName, ActorSpawnInfo(), data);
		spawnedCharacters.push_back(character);
		charactersToPosition.push_back(character);
	}

	PositionCharacters(charactersToPosition);

	return spawnedCharacters;
}