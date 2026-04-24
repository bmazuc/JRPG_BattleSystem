#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "Scene/Actor.h"

class SpriteRendererComponent;
class Sprite;

class Enemy : public Actor
{
public:
	Enemy(const char* spriteFile);
	void Update(float deltaTime) override;

	Sprite* GetSprite() const { return sprite; }
	void SetSpeed(float speed) { enemySpeed = speed; }

private:
	SpriteRendererComponent* spriteRenderer;
	Sprite* sprite;

	float enemyMoveDirection = 1.0f;
	float enemySpeed;
};

#endif // __ENEMY_H_INCLUDED__