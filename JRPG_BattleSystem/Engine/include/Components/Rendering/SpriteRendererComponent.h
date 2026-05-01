#ifndef __SPRITE_RENDERER_COMPONENT_H_INCLUDED__
#define __SPRITE_RENDERER_COMPONENT_H_INCLUDED__

#include "Components/Component.h"
#include "Graphics/Sprite.h"

enum ImageExtension
{
	PNG = 0,
	BPM = 1
};

class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));
	~SpriteRendererComponent();

	Sprite* GetSprite() const { return sprite; }
	
private:
	Sprite* sprite;
};

#endif // __SPRITE_RENDERER_COMPONENT_H_INCLUDED__