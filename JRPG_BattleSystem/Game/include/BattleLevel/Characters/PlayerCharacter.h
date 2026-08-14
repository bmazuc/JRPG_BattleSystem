#ifndef __PLAYER_CHARACTER_H_INCLUDED__
#define __PLAYER_CHARACTER_H_INCLUDED__

#include "Character.h"
#include <map>

class Ability;

struct PlayerCharacterData : CharacterData
{
public:
	PlayerCharacterData() = default;
	PlayerCharacterData(std::string _characterName, std::string _textureName, std::string _shaderName, Color _color, glm::vec2 _spriteSize, CharacterAttributes _attributes, Ability* _skill)
		: CharacterData(_characterName, _textureName, _shaderName, _color, _spriteSize, _attributes), skill(_skill) {}

	Ability* skill;
};

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(PlayerCharacterData data);

	void BeginDestroy() override;

	Ability* TryGetAbility(std::string abilityName);
	const Ability* TryGetAbility(std::string abilityName) const;

private:
	std::map<std::string, Ability*> abilities;
};

#endif // __PLAYER_CHARACTER_H_INCLUDED__
