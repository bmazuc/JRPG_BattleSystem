#ifndef __PLAYER_SPAWNER_H_INCLUDED__
#define __PLAYER_SPAWNER_H_INCLUDED__

#include "CharacterSpawner.h"
#include "BattleLevel/Characters/PlayerCharacter.h"

class PlayerSpawner : public CharacterSpawner
{
public:
	~PlayerSpawner();

	void AddCharacterData(PlayerCharacterData data) { characterDatas.push_back(data); }

	std::vector<PlayerCharacter*> GeneratePlayerGroup();

private:
	std::vector<PlayerCharacterData> characterDatas;
};

#endif // __PLAYER_SPAWNER_H_INCLUDED__