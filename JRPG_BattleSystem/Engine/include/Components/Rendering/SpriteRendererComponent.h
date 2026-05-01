#ifndef __SPRITE_RENDERER_COMPONENT_H_INCLUDED__
#define __SPRITE_RENDERER_COMPONENT_H_INCLUDED__

#include "Components/Component.h"
#include "Rendering/Shader.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

class Material;

/*
 *	A component allowing to render a sprite (2D graphic entity)
 */
class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));
	~SpriteRendererComponent();

	Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }
	int GetLayer() const { return layer; }

	void SetSize(glm::vec2 _size) { size = _size; }
	void SetLayer(int _layer) { layer = _layer; }
	
private:
	glm::vec2 size = glm::vec2(1, 1);
	int layer = 0;

	Material* material;
};

#endif // __SPRITE_RENDERER_COMPONENT_H_INCLUDED__