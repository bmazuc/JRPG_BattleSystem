#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include <string>
#include "Rendering/Color.h"
#include "Core/Delegate/Delegate.h"

class SpriteRendererComponent;

/**
 * Defines the gameplay attributes of a character.
 * Contains both current and maximum resource values, as well as offensive and defensive statistics
 */
struct CharacterAttributes
{
public:
	CharacterAttributes() = default;
	/**
	 * Creates a character attribute set with the specified values.
	 * Current health and mana are initialized to their respective maximum values.
	 */
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

/**
 * Configuration data used to initialize a character.
 * Contains visual information and gameplay attributes required to create a Character instance.
 */
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

/**
 * Base class for playable and non-playable characters.
 *
 * Handles common character functionality such as:
 * - character initialization
 * - gameplay attributes
 * - player input
 * - selection
 * - damage and mana management
 * - regeneration
 * - visual damage feedback
 * - death and destruction
 */
class Character : public Actor
{
public:
	Character() = default;
	Character(CharacterData data);

	void BeginDestroy() override;

	void Update(float deltaTime) override;
		
	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	// Event triggered when the character is selected.
	Delegate<void, Character*> OnSelected;

	void SetBlinkDuration(float _damageDuration) { blinkDuration = _damageDuration; }

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }
	const SpriteRendererComponent* GetSpriteRenderer() const { return spriteRenderer; }

	/**
	 * Applies damage to the character.
	 * Triggers health updates and damage events.
	 * The character is marked for destruction when its health reaches zero.
	 */
	void TakeDamage(int damage);
	/**
	 * Consumes mana from the character.
	 */
	void ConsumeMana(int manaAmount);

	void RestoreHealth(int amount);
	void RestoreMana(int amount);

	/**
	 * Event triggered after the character takes damage.
	 *
	 * @param character Character that received the damage.
	 * @param damage Amount of damage received.
	 */
	Delegate<void, Character*, int> OnDamageTaken;
	// Event triggered when the visual blink effect ends.
	Delegate<void> OnBlinkEnd;
	/**
	 * Event triggered when the character dies.
	 *
	 * @param character Character that died.
	 */
	Delegate<void, Character*> OnDeath;

	/**
	 * Event triggered when the character's health changes.
	 * @param currentHealth Current health value.
	 * @param maxHealth Maximum health value.
	 */
	Delegate<void, int, int> OnHealthUpdate;
	/**
	 * Event triggered when the character's mana changes.
	 *
	 * @param currentMana Current mana value.
	 * @param maxMana Maximum mana value.
	 */
	Delegate<void, int, int> OnManaUpdate;

	void SetCharacterName(std::string inName) { characterName = inName; }
	const std::string& GetCharacterName() const { return characterName; }

	const CharacterAttributes& GetAttributes() { return attributes; }

protected:
	SpriteRendererComponent* spriteRenderer;

	std::string characterName;

	CharacterAttributes attributes;

private:
	/**
	 * Updates the character's visual blink effect.
	 */
	void Blink(float t);
	/**
	 * Marks the character for destruction and triggers the death event.
	 */
	void Kill();

	// Remaining time of the current blink effect.
	float blinkTimer = 0.0f;
	// Duration of the blink effect in seconds.
	float blinkDuration = 0.2f;

	// Character color before the visual feedback effect.
	Color originalColor;
	// Color used during the visual feedback effect.
	Color blinkColor;

	PlayerController* playerController;

	DelegateHandle clickHandle;

	// Indicates that the character is waiting for the blink effect to finish before being destroyed.
	bool isPendingKill = false;
	bool isAlive = true;
};

#endif // __CHARACTER_H_INCLUDED__