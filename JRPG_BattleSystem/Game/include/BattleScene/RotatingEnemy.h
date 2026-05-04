#ifndef __ROTATING_ENEMY_H_INCLUDED__
#define __ROTATING_ENEMY_H_INCLUDED__

#include "Scene/Actor.h"
#include <string>

class SpriteRendererComponent;

class RotatingEnemy : public Actor
{
public:
	RotatingEnemy(std::string textureName = "default", std::string shaderName = "default");
	void Update(float deltaTime) override;
	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }

	void SetSpeed(float speed) { enemySpeed = speed; }

private:
	bool IsHovered(glm::vec2 mousePos);

	SpriteRendererComponent* spriteRenderer;

	PlayerController* playerController;

	bool isRotating = false;

	float enemySpeed;
};

#endif // __ROTATING_ENEMY_H_INCLUDED__