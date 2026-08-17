#ifndef __CHARACTER_SPAWNER_H_INCLUDED__
#define __CHARACTER_SPAWNER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include "BattleLevel/Characters/Character.h"

#include <vector>

class CharacterSpawner : public Actor
{
public:
	void SetSpacing(float newSpacing) { spacing = newSpacing; }

protected:
	void PositionCharacters(std::vector<Character*>& spawnedCharacters);

	float spacing = 0;
};

#endif // __CHARACTER_SPAWNER_H_INCLUDED__