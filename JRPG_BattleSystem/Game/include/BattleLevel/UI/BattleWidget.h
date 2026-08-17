#ifndef __BATTLE_WIDGET_H_INCLUDED__
#define __BATTLE_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"

class Text;
class Scene;
class Image;
class PlayerCharacter;
class PlayerActionsMenu;
class BattleManager;

/**
 * Stores the runtime state of a damage display text.
 * Keeps track of the text widget and the time elapsed since it was displayed, allowing BattleWidget to update its position and transparency over time.
 */
struct DamageDisplayTextData
{
public:
	DamageDisplayTextData(Text* _text) : text(_text) {}

	Text* text;
	float lifeTime = 0.0f;
};

/**
 * Defines the battle UI, including its composition, layout, and appearance.
 * Responsible for:
 * - displaying the current turn
 * - displaying player character information
 * - managing the player action menu
 * - displaying and animating damage numbers
 * This widget encapsulates the construction and visual configuration of its
 * UI elements. Gameplay-specific data is supplied through its public interface.
 */
class BattleWidget : public UserWidget
{
public:
	void Construct() override;

	/**
	 * Creates the UI elements displaying information for the specified characters.
	 */
	void InitCharacterInfos(std::vector<PlayerCharacter*> characters);

	/**
	 * Updates active damage display texts.
	 * Damage texts are moved upward and faded out over their configured lifetime.
	 */ 
	void Update(float deltaTime) override;

	void SetTurnText(std::string content);
	void SetCurrentScene(Scene* scene) { currentScene = scene; }
	void SetDamageTextDuration(float duration) { damageTextDuration = duration; }
	void SetDamageTextSpeed(float speed) { damageTextSpeed = speed; }

	/**
	 * Displays an animated damage amount at a world position.
	 * The world position is converted to screen space using the active camera.
	 */
	void DisplayDamage(glm::vec2 worldPosition, int damageTaken);


	/**
	 * Displays the action menu for the specified player character.
	 */ 
	void ShowPlayerActionsMenu(PlayerCharacter* character);
	/**
	 * Hides the player action menu.
	 */
	void HidePlayerActionsMenu();

	PlayerActionsMenu* GetPlayerActionsMenu() { return playerActionsMenu; }

	// Event triggered when all currently displayed damage texts have been destroyed.
	Delegate<void> OnAllDamageTextDestroy;

private:
	Text* turnText;
	// Current scene ref used to convert world positions into screen positions.
	Scene* currentScene;
	Image* infosBackground;
	PlayerActionsMenu* playerActionsMenu;

	// Damage texts currently being animated.
	std::vector<DamageDisplayTextData> currentDamageTextDisplayed;

	// Duration of a damage text animation in seconds.
	float damageTextDuration = 1.0f;
	// Upward movement speed of damage texts.
	float damageTextSpeed = 30.0f;
};
 
#endif // __BATTLE_WIDGET_H_INCLUDED__