#ifndef __PLAYER_SPAWNER_H_INCLUDED__
#define __PLAYER_SPAWNER_H_INCLUDED__

#include "CharacterSpawner.h"
#include "BattleLevel/Characters/PlayerCharacter.h"

/**
 * Spawner responsible for generating player character groups. Player characters are spawned from the configured character data and arranged into a vertical formation.
 */
class PlayerSpawner : public CharacterSpawner
{
public:
	~PlayerSpawner();

	/**
	 * Adds a character configuration used when spawning player characters.
	 */
	void AddCharacterData(PlayerCharacterData data) { characterDatas.push_back(data); }

	/**
	 * Generates the configured player character group and positions its members.
	 * Characters are spawned in the same order as their configuration data.
	 */
	std::vector<PlayerCharacter*> GeneratePlayerGroup();

private:
	// Character configurations used for player group generation.
	std::vector<PlayerCharacterData> characterDatas;
};

#endif // __PLAYER_SPAWNER_H_INCLUDED__