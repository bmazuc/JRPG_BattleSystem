#include "UI/Image.h"
#include "Rendering/Material.h"

Image::Image(std::string textureName, std::string shaderName, glm::vec4 color)
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