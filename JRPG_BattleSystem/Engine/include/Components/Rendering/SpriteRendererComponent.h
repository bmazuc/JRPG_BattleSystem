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
	/*
	 *	@param textureName the texture used by the material
	 *	@param shaderName the shader used by the material
	 *  @param color the color used by the material
	 */
	SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));
	~SpriteRendererComponent();

	Material* GetMaterial() { return material; }
	const Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }
	int GetZOrder() const { return zOrder; }

	void SetSize(glm::vec2 _size) { size = _size; }
	/*
	 *	The zOrder decides what priority each sprite has to the renderer.
	 *	The lower the number you give it, the further back the sprite appears.
	 */
	void SetZOrder(int _zOrder) { zOrder = _zOrder; }
	
private:
	glm::vec2 size = glm::vec2(1, 1);
	/*
	 *	The zOrder decides what priority each sprite has to the renderer.
	 *	The lower the number you give it, the further back the sprite appears.
	 */ 
	int zOrder = 0;

	Material* material;
};

#endif // __SPRITE_RENDERER_COMPONENT_H_INCLUDED__