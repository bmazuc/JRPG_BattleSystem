#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "Scene/Actor.h"
#include <string>

class SpriteRendererComponent;
class Sprite;

class Enemy : public Actor
{
public:
	Enemy(std::string textureName, std::string shaderName);
	void Update(float deltaTime) override;

	Sprite* GetSprite() const;
	void SetSpeed(float speed) { enemySpeed = speed; }

private:
	SpriteRendererComponent* spriteRenderer;

	float enemyMoveDirection = 1.0f;
	float enemySpeed;

	float timer = 0.0f;
};

#endif // __ENEMY_H_INCLUDED__