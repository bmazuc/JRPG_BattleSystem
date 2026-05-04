#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "Scene/Actor.h"
#include <string>

class SpriteRendererComponent;

class Enemy : public Actor
{
public:
	Enemy(std::string textureName = "default", std::string shaderName = "default");
	void Update(float deltaTime) override;
	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }

	void SetSpeed(float speed) { enemySpeed = speed; }

private:
	bool IsHovered(glm::vec2 mousePos);

	SpriteRendererComponent* spriteRenderer;

	PlayerController* playerController;

	bool isMoving = false;

	float enemyMoveDirection = 1.0f;
	float enemySpeed;
};

#endif // __ENEMY_H_INCLUDED__