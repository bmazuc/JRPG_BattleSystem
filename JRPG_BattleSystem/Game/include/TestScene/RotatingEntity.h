#ifndef __ROTATING_ENTITY_H_INCLUDED__
#define __ROTATING_ENTITY_H_INCLUDED__

#include "Scene/Actor.h"
#include <string>

class SpriteRendererComponent;

class RotatingEntity : public Actor
{
public:
	RotatingEntity(std::string textureName = "default", std::string shaderName = "default");
	void Update(float deltaTime) override;
	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }

	void SetSpeed(float newSpeed) { speed = newSpeed; }

private:
	SpriteRendererComponent* spriteRenderer;

	PlayerController* playerController;

	bool isRotating = false;

	float speed;
};

#endif // __ROTATING_ENTITY_H_INCLUDED__