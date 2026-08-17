#ifndef __BATTLE_MANAGER_H_INCLUDED__
#define __BATTLE_MANAGER_H_INCLUDED__

#include "World/Level/LevelSubsystem.h"
#include "Core/Delegate/Delegate.h"

#include <vector>

class EnemySpawner;
class PlayerSpawner;
class Character;
class Enemy;
class PlayerCharacter;
class PlayerController;

class CountdownWidget;
class BattleWidget;
class GameOverWidget;
class UserWidget;

class Ability;
class AbilityWithActorTarget;

/**
 * Represents the different states of a battle turn.
 *
 * The battle manager uses this state machine to control the flow
 * of the battle and determine which player interactions are allowed.
 */
enum class BattleState
{
	INIT,
	WAIT_FOR_COUNTDOWN_END,
	ENEMY_TURN,
	WAIT_FOR_ACTION_SELECTION,
	WAIT_FOR_TARGET,
	RESOLVING_TURN,
	BATTLE_END
};

/**
 * Allow to gather and config different battle parameters : enemy turn duration, feedbacks duration, ...
 */
struct BattleConfig
{
public:
	// Value used to simulate enemy turn and increase enemy turn readability.
	float enemyTurnDuration = 1.0f;
	float blinkDuration = 1.0f;

	/* Config for countdown */

	float inBetweenCountDuration = 0.75f;
	int count = 3;

	/* Config for damage displayer */

	float damageTextDuration = 1.0f;
	float damageTextSpeed = 30.0f;
};

/**
 * Manages the complete flow of a turn-based battle.
 *
 * Responsible for:
 * - battle initialization and character spawning
 * - turn order generation and progression
 * - player action and target selection
 * - enemy turn simulation
 * - action resolution and visual feedback synchronization
 * - battle state management
 * - battle UI coordination
 * - battle end conditions
 *
 * The battle flow is controlled through BattleState, allowing gameplay
 * actions, input and visual feedback to be processed independently.
 */
class BattleManager : public LevelSubsystem
{
public:
	/**
	 * Initializes the battle and starts the opening countdown.
	 */
	void Initialize() override;
	void Update(float deltaTime) override;

	void SetPlayerController(PlayerController* inPlayerController);

	void SetEnemySpawner(EnemySpawner* newEnemySpawner) { enemySpawner = newEnemySpawner; }
	void SetPlayerSpawner(PlayerSpawner* newPlayerSpawner) { playerSpawner = newPlayerSpawner; }

	void SetCurrentAbility(Ability* inAbility);

	void SetBattleWidget(BattleWidget* widget);
	void SetCountdownWidget(CountdownWidget* widget);
	void SetGameOverwidget(GameOverWidget* widget) { gameOverWidget = widget; }

	void SetBattleConfig(BattleConfig& config) { battleConfig = config; }

	/**
	 * Ends the current battle and displays the game over screen.
	 */
	void EndBattle();

private:
	/**
	 * Builds a randomized turn order from all living characters.
	 */
	void GenerateTurnOrder();
	/**
	 * Advances to the next character in the turn order.
	 */
	void NextTurn();

	void OnBattleWidgetConstruct(UserWidget* widget);
	void OnPlayerActionsMenuConstruct(UserWidget* widget);

	/**
	 * Spawns and initializes all player characters participating in the battle.
	 */
	void SpawnPlayerCharacters();
	/**
	 * Spawns and initializes the current group of enemies.
	 */
	void SpawnEnemies();

	void OnAllDamageTextDestroy();
	/**
	 * Displays visual feedback for damage or regeneration applied to a character.
	 */
	void OnCharacterTakeDamage(Character* character, int damage);
	/**
	 * Handles player character death and removes the character from the active turn order.
	 */
	void OnPlayerCharacterDeath(Character* playerCharacter);
	/**
	 * Handles enemy death, removes the enemy from the active turn order, and updates the kill counter.
	 */
	void OnEnemyDeath(Character* enemy);
	void OnBlinkEnd();

	/**
	 * Handles right-click input used to cancel target selection.
	 */
	void OnRightClick();
	void OnPlayerCharacterSelected(Character* selectedCharacter);
	void OnEnemySelected(Character* selectedCharacter);

	/**
	 * Starts the battle once the initial countdown has completed.
	 */
	void OnCountdownEnd();

private:

	PlayerSpawner* playerSpawner;
	EnemySpawner* enemySpawner;

	// Characters participating in the current battle.

	std::vector<PlayerCharacter*> playerCharacters;
	std::vector<Enemy*> enemies;

	// Randomized order in which characters take their turns.
	std::vector<Character*> turnOrder;

	// Index of the next character in the turn order.
	int turnIndex = 0;

	BattleState currentState;

	CountdownWidget* countdownWidget;
	BattleWidget* battleWidget;
	GameOverWidget* gameOverWidget;

	BattleConfig battleConfig;

	// Remaining delay before an enemy executes its action.
	float currentEnemyTurnDuration;

	DelegateHandle OnAllDamageTextDestroyHandle;
	DelegateHandle OnBattleWidgetConstructHandle;
	DelegateHandle OnPlayerActionsMenuConstructHandle;

	Character* currentCharacter;

	// Action resolution waits for visual feedback to complete.

	bool waitingForBlinkEnd = false;
	bool waitingForDamageTextDestroy = false;

	// Number of enemies defeated during the battle.
	int killCount = 0;

	// Currently selected targeted ability.
	AbilityWithActorTarget* currentAbilityWithActorTarget = nullptr;

	PlayerController* playerController;
	DelegateHandle OnRightClickHandle;
};

#endif // __BATTLE_MANAGER_H_INCLUDED__