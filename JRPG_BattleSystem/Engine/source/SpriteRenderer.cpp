#include "SpriteRenderer.h"

Sprite* SpriteRenderer::CreateSprite(const char* file, ImageExtension extension)
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

SpriteRenderer::~SpriteRenderer()
{
	delete sprite;
	sprite = nullptr;
}