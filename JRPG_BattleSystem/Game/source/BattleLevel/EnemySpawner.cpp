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
	float totalHeight = 0;
	for (const Enemy* enemy : spawnedEnemies)
	{
		const SpriteRendererComponent* spriteRender = enemy->GetSpriteRenderer();
		totalHeight += spriteRender->GetSize().y * spriteRender->GetWorldScale().y;
	}
	totalHeight += spacing * (spawnedEnemies.size() - 1);

	// Find start
	glm::vec2 position = GetWorldPosition();
	float start = position.y - totalHeight / 2.0f;

	// Position each enemy
	float y = start;

	for (Enemy* enemy : spawnedEnemies)
	{
		const SpriteRendererComponent* spriteRender = enemy->GetSpriteRenderer();
		float size = spriteRender->GetSize().y * spriteRender->GetWorldScale().y;

		enemy->SetWorldPosition(glm::vec2(position.x, y + size / 2));

		y += size + spacing;
	}
}