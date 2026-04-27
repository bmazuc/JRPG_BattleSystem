#include "Image.h"
#include "Core/ResourceManager.h"
#include "Graphics/Material.h"

Image::Image(std::string textureName, std::string shaderName, glm::vec3 color)
{
	material = new Material(textureName, shaderName, color);
}

Image::~Image()
{
	delete material;
	material = nullptr;
}