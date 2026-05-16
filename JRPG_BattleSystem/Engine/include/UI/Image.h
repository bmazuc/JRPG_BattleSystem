#ifndef __IMAGE_H_INCLUDED__
#define __IMAGE_H_INCLUDED__

#include "Widget.h"

#include "Rendering/IRenderable.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Material;

/**
 * Widget that displays a textured quad.
 *
 * Image is a basic visual building block for UI:
 * - renders a texture using a material
 * - supports scaling via size
 * - used as base for interactive widgets (e.g. Button)
 */
class Image : public Widget, public IRenderable
{
public:
	Image(std::string textureName = "default", std::string shaderName = "default", glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	
	~Image();

	Material* GetMaterial() { return material; }
	const Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }

	void SetSize(glm::vec2 newSize) { size = newSize; }

	void AddToRenderQueue(RenderQueue& queue) override;

protected:
	glm::vec2 size = glm::vec2(1.0f, 1.0f);

	// Rendering material (texture + shader + color)
	Material* material;
};

#endif // __IMAGE_H_INCLUDED__