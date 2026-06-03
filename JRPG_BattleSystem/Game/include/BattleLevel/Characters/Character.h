#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__

#include "World/Level/Scene/Actor.h"
#include <string>
#include <glm/vec3.hpp>
#include "Core/Delegate/Delegate.h"

class SpriteRendererComponent;

struct CharacterData
{
public:
	CharacterData() = default;
	CharacterData(std::string _textureName, std::string _shaderName, glm::vec3 _color, glm::vec2 _spriteSize) 
		: textureName(_textureName), shaderName(_shaderName), color(_color), spriteSize(_spriteSize) {}

	std::string textureName = "default";
	std::string shaderName = "default";
	glm::vec3 color = glm::vec3(1, 1, 1);

	glm::vec2 spriteSize = glm::vec2(1, 1);
};

class Character : public Actor
{
public:
	Character(CharacterData);

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }
	const SpriteRendererComponent* GetSpriteRenderer() const { return spriteRenderer; }

	void Kill();

	Delegate<void, Character*> OnDeath;

protected:
	SpriteRendererComponent* spriteRenderer;
	bool isAlive = true;
};

#endif // __CHARACTER_H_INCLUDED__