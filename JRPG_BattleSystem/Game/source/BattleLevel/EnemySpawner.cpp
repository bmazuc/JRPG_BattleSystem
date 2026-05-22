#include "BattleLevel/EnemySpawner.h"
#include "Core/Random.h"
#include "World/Level/Level.h"
#include "Components/Rendering/SpriteRendererComponent.h"

EnemySpawner::~EnemySpawner()
{
	enemyDatas.clear();
}

std::vector<Enemy*> EnemySpawner::GenerateEnemies()
{
	std::vector<Enemy*> spawnedEnemies;

	for (unsigned int idx = 0; idx < groupSize; idx++)
	{
		const EnemyData& data = enemyDatas.size() > 0 ?
			enemyDatas[Random::FromRange(0, (int)enemyDatas.size() - 1)] :
			EnemyData();

		Enemy* enemy = GetScene()->SpawnActor<Enemy>("Enemy" + std::to_string(idx), ActorSpawnInfo(), data);
		spawnedEnemies.push_back(enemy);
	}

	PositionEnemies(spawnedEnemies);

	return spawnedEnemies;
}

void EnemySpawner::PositionEnemies(std::vector<Enemy*>& spawnedEnemies)
{
	// Compute total width
	float totalWidth = 0;
	for (const Enemy* enemy : spawnedEnemies)
	{
		const SpriteRendererComponent* spriteRender = enemy->GetSpriteRenderer();
		totalWidth += spriteRender->GetSize().x * spriteRender->GetWorldScale().x;
	}
	totalWidth += spacing * (spawnedEnemies.size() - 1);

	// Find start
	glm::vec2 position = GetWorldPosition();
	float start = position.x - totalWidth / 2.0f;

	// Position each enemy
	float x = start;

	for (Enemy* enemy : spawnedEnemies)
	{
		const SpriteRendererComponent* spriteRender = enemy->GetSpriteRenderer();
		float size = spriteRender->GetSize().x * spriteRender->GetWorldScale().x;

		enemy->SetWorldPosition(glm::vec2(x + size/2, position.y));

		x += size + spacing;
	}
}