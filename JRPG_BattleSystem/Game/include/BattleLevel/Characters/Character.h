#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include <string>
#include <glm/vec3.hpp>
#include "Core/Delegate/Delegate.h"

class SpriteRendererComponent;

struct CharacterData
{
public:
	CharacterData() = default;
	CharacterData(std::string _characterName, std::string _textureName, std::string _shaderName, glm::vec4 _color, glm::vec2 _spriteSize)
		: characterName(_characterName), textureName(_textureName), shaderName(_shaderName), color(_color), spriteSize(_spriteSize) {}

	std::string characterName = "";
	std::string textureName = "default";
	std::string shaderName = "default";
	glm::vec4 color = glm::vec4(1, 1, 1, 1);

	glm::vec2 spriteSize = glm::vec2(1, 1);
};

struct CharacterAttributes
{
	int health = 3;
	int maxHealth = 3;

	int mana = 3;
	int maxMana = 3;

	int attack = 2;
	int defense = 1;
};

class Character : public Actor
{
public:
	Character(CharacterData);

	void Update(float deltaTime) override;
		
	void SetDamageDuration(float _damageDuration) { damageDuration = _damageDuration; }

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }
	const SpriteRendererComponent* GetSpriteRenderer() const { return spriteRenderer; }

	void TakeDamage(int damage);

	Delegate<void, Character*, int> OnDamageTaken;
	Delegate<void> OnBlinkEnd;
	Delegate<void, Character*> OnDeath;

	Delegate<void, int, int> OnHealthUpdate;
	Delegate<void, int, int> OnManaUpdate;

	glm::vec4 originalColor;

	void SetCharacterName(std::string inName) { name = inName; }
	const std::string& GetCharacterName() const { return name; }

	const CharacterAttributes& GetAttributes() { return attributes; }

private:
	void Blink(float t);
	void Kill();

protected:
	float damageTimer = 0.0f;
	float damageDuration = 0.2f;

	SpriteRendererComponent* spriteRenderer;
	bool isAlive = true;
	bool isPendingKill = false;

	std::string characterName;

	CharacterAttributes attributes;
};

#endif // __CHARACTER_H_INCLUDED__