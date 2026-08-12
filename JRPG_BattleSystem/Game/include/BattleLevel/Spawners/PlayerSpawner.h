#ifndef __PLAYER_SPAWNER_H_INCLUDED__
#define __PLAYER_SPAWNER_H_INCLUDED__

#include "CharacterSpawner.h"

class PlayerCharacter;

class PlayerSpawner : public CharacterSpawner
{
public:
	std::vector<PlayerCharacter*> GeneratePlayerGroup();
};

#endif // __PLAYER_SPAWNER_H_INCLUDED__