#include "Image.h"

void Image::LoadBMP(const char* file)
{
	texture = new Texture();
	texture->LoadBMP(file);
}

void Image::LoadPNG(const char* file)
{
	texture = new Texture();
	texture->LoadPNG(file);
}

Image::~Image()
{
	delete texture;
	texture = nullptr;
}