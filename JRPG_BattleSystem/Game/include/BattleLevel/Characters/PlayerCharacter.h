#ifndef __PLAYER_CHARACTER_H_INCLUDED__
#define __PLAYER_CHARACTER_H_INCLUDED__

#include "Character.h"
#include <map>

class Ability;

/**
 * Configuration data used to initialize a player character.
 * Extends CharacterData with the character's unique skill ability.
 */
struct PlayerCharacterData : CharacterData
{
public:
	PlayerCharacterData() = default;
	PlayerCharacterData(std::string _characterName, std::string _textureName, std::string _shaderName, Color _color, glm::vec2 _spriteSize, CharacterAttributes _attributes, Ability* _skill)
		: CharacterData(_characterName, _textureName, _shaderName, _color, _spriteSize, _attributes), skill(_skill) {}

	Ability* skill;
};

/**
 * Playable character controlled by the player.
 * Extends Character with a collection of abilities, including basic attack, unique skill, and flee actions.
 */
class PlayerCharacter : public Character
{
public:
	PlayerCharacter(PlayerCharacterData data);

	void BeginDestroy() override;

	/**
	 * Searches for an ability by name.
	 */
	Ability* TryGetAbility(std::string abilityName);
	const Ability* TryGetAbility(std::string abilityName) const;

private:
	// Abilities owned by the player character, indexed by name.
	std::map<std::string, Ability*> abilities;
};

#endif // __PLAYER_CHARACTER_H_INCLUDED__
