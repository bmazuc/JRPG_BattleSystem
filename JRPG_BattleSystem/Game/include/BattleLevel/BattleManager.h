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

class BattleManager : public LevelSubsystem
{
public:
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

	void EndBattle();

private:
	void GenerateTurnOrder();
	void NextTurn();

	void OnBattleWidgetConstruct(UserWidget* widget);
	void OnPlayerActionsMenuConstruct(UserWidget* widget);

	void SpawnPlayerCharacters();
	void SpawnEnemies();

	void OnAllDamageTextDestroy();
	void OnCharacterTakeDamage(Character* character, int damage);
	void OnPlayerCharacterDeath(Character* playerCharacter);
	void OnEnemyDeath(Character* enemy);
	void OnBlinkEnd();

	void OnRightClick();
	void OnEnemySelected(Enemy* selectedEnemy);

	void InflictDamage(Character* attacker, Character* Defender);

	void OnCountdownEnd();

private:

	PlayerSpawner* playerSpawner;
	EnemySpawner* enemySpawner;

	std::vector<PlayerCharacter*> playerCharacters;
	std::vector<Enemy*> enemies;
	std::vector<Character*> turnOrder;

	int turnIndex = 0;

	BattleState currentState;

	CountdownWidget* countdownWidget;
	BattleWidget* battleWidget;
	GameOverWidget* gameOverWidget;

	BattleConfig battleConfig;

	float currentEnemyTurnDuration;

	DelegateHandle OnAllDamageTextDestroyHandle;
	DelegateHandle OnBattleWidgetConstructHandle;
	DelegateHandle OnPlayerActionsMenuConstructHandle;

	Character* currentCharacter;

	bool waitingForBlinkEnd = false;
	bool waitingForDamageTextDestroy = false;

	int killCount = 0;

	AbilityWithActorTarget* currentAbilityWithActorTarget = nullptr;

	PlayerController* playerController;
	DelegateHandle OnRightClickHandle;
};

#endif // __BATTLE_MANAGER_H_INCLUDED__