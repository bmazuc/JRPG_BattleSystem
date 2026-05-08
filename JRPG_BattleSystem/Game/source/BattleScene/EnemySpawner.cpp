#include "BattleScene/EnemySpawner.h"
#include "Core/Random.h"
#include "Scene/Scene.h"
#include "Components/Rendering/SpriteRendererComponent.h"

EnemySpawner::~EnemySpawner()
{
	enemyDatas.clear();
	spawnedEnemies.clear();
}

void EnemySpawner::BeginPlay()
{
	GenerateEnemies();
}

void EnemySpawner::GenerateEnemies()
{
	for (unsigned int idx = 0; idx < groupSize; idx++)
	{
		const EnemyData& data = enemyDatas.size() > 0 ?
			enemyDatas[Random::FromRange(0, (int)enemyDatas.size() - 1)] :
			EnemyData();

		Enemy* enemy = GetScene()->SpawnActor<Enemy>("Enemy" + std::to_string(idx), ActorSpawnInfo(), data);
		spawnedEnemies.push_back(enemy);
	}

	PositionEnemies();
}

void EnemySpawner::PositionEnemies()
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