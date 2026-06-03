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

	// Temp value used to simulate enemy turn.
	float timer;
};

#endif // __BATTLE_MANAGER_H_INCLUDED__