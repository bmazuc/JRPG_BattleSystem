#ifndef __IMAGE_H_INCLUDED__
#define __IMAGE_H_INCLUDED__

#include "UIElement.h"

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Material;

class Image : public UIElement
{
public:
	Image(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));
	~Image();

	Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }

	void SetSize(glm::vec2 _size) { size = _size; }

private:
	glm::vec2 size = glm::vec2(1, 1);

	Material* material;
};

#endif // __IMAGE_H_INCLUDED__