#ifndef __MOVING_ENTITY_H_INCLUDED__
#define __MOVING_ENTITY_H_INCLUDED__

#include "Scene/Actor.h"
#include <string>

class SpriteRendererComponent;

class MovingEntity : public Actor
{
public:
	MovingEntity(std::string textureName = "default", std::string shaderName = "default");
	void Update(float deltaTime) override;
	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }

	void SetSpeed(float newSpeed) { speed = newSpeed; }

private:
	bool IsHovered(glm::vec2 mousePos);

	SpriteRendererComponent* spriteRenderer;

	PlayerController* playerController;

	bool isMoving = false;

	float moveDirection = 1.0f;
	float speed;
};

#endif // __MOVING_ENTITY_H_INCLUDED__