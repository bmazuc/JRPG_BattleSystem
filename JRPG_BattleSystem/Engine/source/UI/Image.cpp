#include "UI/Image.h"
#include "Core/Resource/ResourceManager.h"
#include "Rendering/Material.h"

Image::Image(std::string textureName, std::string shaderName, glm::vec3 color)
{
	material = new Material(textureName, shaderName, color);
}

Image::~Image()
{
	delete material;
	material = nullptr;
}

void Image::AddToRenderQueue(RenderQueue& queue)
{
	queue.AddUIItem(new RenderTextureItem(GetTransform().world, size, material));
}