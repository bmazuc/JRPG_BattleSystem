#include "Graphics/Sprite.h"

void Sprite::LoadBMP(const char* file)
{
	texture = new Texture();
	texture->LoadBMP(file);
}

void Sprite::LoadPNG(const char* file)
{
	texture = new Texture();
	texture->LoadPNG(file);
}

Sprite::~Sprite()
{
	delete texture;
	texture = nullptr;
}