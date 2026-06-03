#include "BattleLevel/Spawners/CharacterSpawner.h"
#include "Components/Rendering/SpriteRendererComponent.h"

CharacterSpawner::~CharacterSpawner()
{
	characterDatas.clear();
}

void CharacterSpawner::PositionCharacters(std::vector<Character*>& spawnedCharacters)
{
	// Compute total width
	float totalHeight = 0;
	for (const Character* character : spawnedCharacters)
	{
		const SpriteRendererComponent* spriteRenderer = character->GetSpriteRenderer();
		totalHeight += spriteRenderer->GetSize().y * spriteRenderer->GetWorldScale().y;
	}
	totalHeight += spacing * (spawnedCharacters.size() - 1);

	// Find start
	glm::vec2 position = GetWorldPosition();
	float start = position.y - totalHeight / 2.0f;

	// Position each enemy
	float y = start;

	for (Character* character : spawnedCharacters)
	{
		const SpriteRendererComponent* spriteRenderer = character->GetSpriteRenderer();
		float size = spriteRenderer->GetSize().y * spriteRenderer->GetWorldScale().y;

		character->SetWorldPosition(glm::vec2(position.x, y + size / 2));

		y += size + spacing;
	}
}