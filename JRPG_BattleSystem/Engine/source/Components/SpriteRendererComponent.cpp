#include "Components/SpriteRendererComponent.h"
#include <glm/ext/matrix_transform.hpp>

Sprite* SpriteRendererComponent::CreateSprite(const char* file, ImageExtension extension)
{
	sprite = new Sprite();
	switch (extension)
	{
	case ImageExtension::PNG:
		sprite->LoadPNG(file);
		break;
	case ImageExtension::BPM:
		sprite->LoadBMP(file);
		break;
	default: break;
	}

	return sprite;
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	delete sprite;
	sprite = nullptr;
}
