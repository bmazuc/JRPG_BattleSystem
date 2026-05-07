#ifndef __KILLABLE_ENTITY_H_INCLUDED__
#define __KILLABLE_ENTITY_H_INCLUDED__

#include "Scene/Actor.h"
#include "Core/Delegate/Delegate.h"
#include <string>

class SpriteRendererComponent;

class KillableEntity : public Actor
{
public:
	KillableEntity(std::string textureName = "default", std::string shaderName = "default");

	void SetupInputs(PlayerController* _playerController) override;

	void OnClick();

	SpriteRendererComponent* GetSpriteRenderer() { return spriteRenderer; }

private:
	bool IsHovered(glm::vec2 mousePos);

	SpriteRendererComponent* spriteRenderer;

	PlayerController* playerController;

	DelegateHandle clickHandle;
};

#endif // __KILLABLE_ENTITY_H_INCLUDED__