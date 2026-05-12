#ifndef __IMAGE_H_INCLUDED__
#define __IMAGE_H_INCLUDED__

#include "UIElement.h"

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Material;

/**
 * UI element that displays a textured quad.
 *
 * Image is a basic visual building block for UI:
 * - renders a texture using a material
 * - supports scaling via size
 * - used as base for interactive widgets (e.g. Button)
 */
class Image : public UIElement
{
public:
	Image(std::string textureName = "default", std::string shaderName = "default", glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	
	~Image();

	Material* GetMaterial() { return material; }
	const Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }

	void SetSize(glm::vec2 newSize) { size = newSize; }

protected:
	glm::vec2 size = glm::vec2(1.0f, 1.0f);

	// Rendering material (texture + shader + color)
	Material* material;
};

#endif // __IMAGE_H_INCLUDED__