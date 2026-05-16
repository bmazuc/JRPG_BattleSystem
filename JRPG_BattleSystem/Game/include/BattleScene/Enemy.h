#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "Scene/Actor.h"
#include <string>
#include <glm/vec3.hpp>
#include "Core/Delegate/Delegate.h"

class SpriteRendererComponent;

struct EnemyData
{
public:
	std::string textureName = "default";
	std::string shaderName = "default";
	glm::vec3 color = glm::vec3(1, 1, 1);

	glm::vec2 spriteSize = glm::vec2(1, 1);
};

class Enemy : public Actor
{
public:
	Enemy(EnemyData data);
	void BeginDestroy() override;

	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }
	const SpriteRendererComponent* GetSpriteRenderer() const { return spriteRenderer; }

	Delegate<void> OnDeath;

private:
	PlayerController* playerController;
	SpriteRendererComponent* spriteRenderer;

	DelegateHandle clickHandle;
};

#endif // __ENEMY_H_INCLUDED__