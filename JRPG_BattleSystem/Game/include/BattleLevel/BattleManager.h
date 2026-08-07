#ifndef __BATTLE_MANAGER_H_INCLUDED__
#define __BATTLE_MANAGER_H_INCLUDED__

#include "World/Level/LevelSubsystem.h"
#include "Core/Delegate/Delegate.h"

#include <vector>

enum class TurnType
{
	None,
	PlayerTurn,
	EnemyTurn
};

class EnemySpawner;
class PlayerSpawner;
class Character;
class Enemy;
class BattleWidget;

/**
 * Allow to gather and config different battle parameters : enemy turn duration, feedbacks duration, ...
 */
struct BattleConfig
{
public:
	// Value used to simulate enemy turn and increase enemy turn readability.
	float enemyTurnDuration = 1.0f;
	float blinkDuration = 1.0f;
	float damageTextDuration = 1.0f;
	float damageTextSpeed = 30.0f;
};

class BattleManager : public LevelSubsystem
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;

	void SetEnemySpawner(EnemySpawner* newEnemySpawner) { enemySpawner = newEnemySpawner; }
	void SetPlayerSpawner(PlayerSpawner* newPlayerSpawner) { playerSpawner = newPlayerSpawner; }
	void SetBattleWidget(BattleWidget* widget);
	void SetBattleConfig(BattleConfig& config) { battleConfig = config; }

private:
	void GenerateTurnOrder();
	void NextTurn();

	void SpawnPlayerCharacters();
	void SpawnEnemies();

	void OnAllDamageTextDestroy();
	void OnCharacterTakeDamage(Character* character, int damage);
	void OnPlayerCharacterDeath(Character* playerCharacter);
	void OnEnemyDeath(Character* enemy);
	void OnBlinkEnd();

	void OnEnemySelected(Enemy* selectedEnemy);

	void InitPlayerTurn();
	void InitEnemyTurn();

	void InflictDamage(Character* attacker, Character* Defender);

	PlayerSpawner* playerSpawner;
	EnemySpawner* enemySpawner;

	std::vector<Character*> playerCharacters;
	std::vector<Enemy*> enemies;
	std::vector<Character*> turnOrder;

	TurnType currentTurn = TurnType::None;
	int turnIndex = 0;

	BattleWidget* battleWidget;

	BattleConfig battleConfig;

	float currentEnemyTurnDuration;

	DelegateHandle OnAllDamageTextDestroyHandle;

	Character* currentCharacter;

	bool resolvingTurn = false;
	bool waitingForBlinkEnd = false;
	bool waitingForDamageTextDestroy = false;
};

#endif // __BATTLE_MANAGER_H_INCLUDED__