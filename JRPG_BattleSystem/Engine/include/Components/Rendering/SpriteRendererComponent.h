#ifndef __SPRITE_RENDERER_COMPONENT_H_INCLUDED__
#define __SPRITE_RENDERER_COMPONENT_H_INCLUDED__

#include "Components/SceneComponent.h"
#include "Rendering/IRenderable.h"

class Material;

/*
 * Component responsible for rendering a 2D sprite.
 */
class SpriteRendererComponent : public SceneComponent, public IRenderable
{
public:
	/**
	 * Creates a sprite renderer using the specified material settings.
	 */
	SpriteRendererComponent(std::string textureName = "default", std::string shaderName = "default", Color color = Colors::White);
	~SpriteRendererComponent();

	Material* GetMaterial() { return material; }
	const Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }
	int GetZOrder() const { return zOrder; }

	void SetSize(glm::vec2 newSize) { size = newSize; }
	void SetZOrder(int newZOrder) { zOrder = newZOrder; }
	
	void SetVisible(bool state) { GetNode()->SetVisible(state); }
	bool IsVisible() const { return GetNode()->IsVisible(); }
	bool IsEffectivelyVisible() const { return GetNode()->IsEffectivelyVisible(); }

	/**
	 * Returns true is mouse currently hover this sprite.
	 */
	bool IsHovered(glm::vec2 mousePos);

	void AddToRenderQueue(RenderQueue& queue) override;

private:
	glm::vec2 size = glm::vec2(1.0f, 1.0f);

	// Lower z-order values are rendered behind higher ones.
	int zOrder = 0;

	Material* material;

	bool isVisible = true;
};

#endif // __SPRITE_RENDERER_COMPONENT_H_INCLUDED__