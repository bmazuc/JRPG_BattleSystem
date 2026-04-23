#ifndef __SPRITE_RENDERER_COMPONENT_H_INCLUDED__
#define __SPRITE_RENDERER_COMPONENT_H_INCLUDED__

#include "Component.h"
#include "Graphics/Sprite.h"

enum ImageExtension
{
	PNG = 0,
	BPM = 1
};

class SpriteRendererComponent : public Component
{
public:
	~SpriteRendererComponent();

	Sprite* CreateSprite(const char* file, ImageExtension extension = ImageExtension::PNG);
	Sprite* GetSprite() const { return sprite; }
	
private:
	Sprite* sprite;
};

#endif // __SPRITE_RENDERER_COMPONENT_H_INCLUDED__