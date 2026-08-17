#ifndef __CHARACTER_SPAWNER_H_INCLUDED__
#define __CHARACTER_SPAWNER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include "BattleLevel/Characters/Character.h"

#include <vector>

/**
 * Base class for character spawners.
 * 
 * Characters are arranged vertically around the spawner position, using a configurable spacing between each character.
 */
class CharacterSpawner : public Actor
{
public:
	void SetSpacing(float newSpacing) { spacing = newSpacing; }

protected:
	/**
	 * Positions spawned characters in a vertical formation.
	 * The formation is centered around the spawner world position and takes each character's rendered size and world scale into account.
	 */
	void PositionCharacters(std::vector<Character*>& spawnedCharacters);

	// Distance between two consecutive characters in the formation.
	float spacing = 0;
};

#endif // __CHARACTER_SPAWNER_H_INCLUDED__