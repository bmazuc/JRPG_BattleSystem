#ifndef __PLAYER_CHARACTER_H_INCLUDED__
#define __PLAYER_CHARACTER_H_INCLUDED__

#include "Character.h"
#include <map>

class Ability;

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(CharacterData data);

	void BeginDestroy() override;

	Ability* TryGetAbility(std::string abilityName);
	const Ability* TryGetAbility(std::string abilityName) const;

private:
	std::map<std::string, Ability*> abilities;
};

#endif // __PLAYER_CHARACTER_H_INCLUDED__
