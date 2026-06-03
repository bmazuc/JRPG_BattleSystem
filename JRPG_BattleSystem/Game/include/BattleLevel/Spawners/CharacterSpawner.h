#ifndef __CHARACTER_SPAWNER_H_INCLUDED__
#define __CHARACTER_SPAWNER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include "BattleLevel/Characters/Character.h"

#include <vector>

class CharacterSpawner : public Actor
{
public:
	~CharacterSpawner();
	void AddCharacterData(CharacterData data) { characterDatas.push_back(data); }

	void SetSpacing(float newSpacing) { spacing = newSpacing; }

protected:
	void PositionCharacters(std::vector<Character*>& spawnedCharacters);

	unsigned int groupSize = 3;
	float spacing = 0;

	std::vector<CharacterData> characterDatas;
};

#endif // __CHARACTER_SPAWNER_H_INCLUDED__