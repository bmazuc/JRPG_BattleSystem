#ifndef __PLAYER_SPAWNER_H_INCLUDED__
#define __PLAYER_SPAWNER_H_INCLUDED__

#include "CharacterSpawner.h"

class PlayerSpawner : public CharacterSpawner
{
public:
	std::vector<Character*> GeneratePlayerGroup();
};

#endif // __PLAYER_SPAWNER_H_INCLUDED__