#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "Scene/Actor.h"

class SpriteRendererComponent;
class Sprite;

class Enemy : public Actor
{
public:
	Enemy(const char* _spriteFile, float _enemySpeed);
	void Init() override;
	void Update(float deltaTime) override;

	void SetSpeed(float speed) { enemySpeed = speed; }

private:
	SpriteRendererComponent* spriteRenderer;
	Sprite* sprite;

	const char* spriteFile;
	float enemyMoveDirection = 1.0f;
	float enemySpeed;
};

#endif // __ENEMY_H_INCLUDED__