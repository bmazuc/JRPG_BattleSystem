#ifndef __BATTLE_MANAGER_H_INCLUDED__
#define __BATTLE_MANAGER_H_INCLUDED__

#include "World/Level/LevelSubsystem.h"
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
class Text;

class BattleManager : public LevelSubsystem
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;

	void SetEnemySpawner(EnemySpawner* newEnemySpawner) { enemySpawner = newEnemySpawner; }
	void SetPlayerSpawner(PlayerSpawner* newPlayerSpawner) { playerSpawner = newPlayerSpawner; }
	void SetTurnText(Text* text) { turnText = text; }
	void SetEnemyTurnDuration(float duration) { enemyTurnDuration = duration; }

private:
	void GenerateTurnOrder();
	void NextTurn();

	void SpawnPlayerCharacters();
	void SpawnEnemies();

	void OnPlayerCharacterDeath(Character* playerCharacter);
	void OnEnemyDeath(Character* enemy);

	void OnEnemySelected(Enemy* selectedEnemy);

	void InitPlayerTurn();
	void InitEnemyTurn();

	void StartNextBattle();

	PlayerSpawner* playerSpawner;
	EnemySpawner* enemySpawner;

	std::vector<Character*> playerCharacters;
	std::vector<Enemy*> enemies;
	std::vector<Character*> turnOrder;

	TurnType currentTurn = TurnType::None;
	int turnIndex = 0;

	Text* turnText;

	// Value used to simulate enemy turn and increase enemy turn readability.
	float enemyTurnDuration = 1.0f;
	float currentEnemyTurnDuration;

	bool resolvingTurn = false;
};

#endif // __BATTLE_MANAGER_H_INCLUDED__