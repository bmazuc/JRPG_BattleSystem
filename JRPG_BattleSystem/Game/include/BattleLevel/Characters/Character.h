#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include <string>
#include "Rendering/Color.h"
#include "Core/Delegate/Delegate.h"

class SpriteRendererComponent;

struct CharacterAttributes
{
public:
	CharacterAttributes() = default;
	CharacterAttributes(int _maxHealth, int _maxMana, int _attack, int _defense, int _magickAttack, int _magickDefense)
		: health(_maxHealth), maxHealth(_maxHealth), mana(_maxMana), maxMana(_maxMana), attack(_attack), defense(_defense), magickAttack(_magickAttack), magickDefense(_magickDefense) {
	}

	int health = 3;
	int maxHealth = 3;

	int mana = 3;
	int maxMana = 3;

	int attack = 2;
	int defense = 1;

	int magickAttack = 2;
	int magickDefense = 0;
};

struct CharacterData
{
public:
	CharacterData() = default;
	CharacterData(std::string _characterName, std::string _textureName, std::string _shaderName, Color _color, glm::vec2 _spriteSize, CharacterAttributes _attributes)
		: characterName(_characterName), textureName(_textureName), shaderName(_shaderName), color(_color), spriteSize(_spriteSize), attributes(_attributes) {}

	virtual ~CharacterData() = default;

	std::string characterName = "";
	std::string textureName = "default";
	std::string shaderName = "default";
	Color color = Colors::White;

	glm::vec2 spriteSize = glm::vec2(1, 1);

	CharacterAttributes attributes;
};

class Character : public Actor
{
public:
	Character() = default;
	Character(CharacterData data);

	void BeginDestroy() override;

	void Update(float deltaTime) override;
		
	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	Delegate<void, Character*> OnSelected;

	void SetDamageDuration(float _damageDuration) { blinkDuration = _damageDuration; }

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }
	const SpriteRendererComponent* GetSpriteRenderer() const { return spriteRenderer; }

	void TakeDamage(int damage);
	void UseMana(int manaAmount);
	void Regen(int healthRegen, int manaRegen);

	Delegate<void, Character*, int> OnDamageTaken;
	Delegate<void> OnBlinkEnd;
	Delegate<void, Character*> OnDeath;

	Delegate<void, int, int> OnHealthUpdate;
	Delegate<void, int, int> OnManaUpdate;

	void SetCharacterName(std::string inName) { name = inName; }
	const std::string& GetCharacterName() const { return name; }

	const CharacterAttributes& GetAttributes() { return attributes; }

private:
	void Blink(float t);
	void Kill();

protected:
	float blinkTimer = 0.0f;
	float blinkDuration = 0.2f;

	Color originalColor;
	Color blinkColor;

	SpriteRendererComponent* spriteRenderer;
	bool isAlive = true;
	bool isPendingKill = false;

	std::string characterName;

	CharacterAttributes attributes;

private:
	PlayerController* playerController;

	DelegateHandle clickHandle;
};

#endif // __CHARACTER_H_INCLUDED__