#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include "RenderQueue.h"

class CameraComponent;
class Texture;
class Shader;
class World;

/**
 * OpenGL-based renderer responsible for world and UI rendering.
 *
 * Handles:
 * - sprite rendering
 * - text rendering
 * - render batching (z-order buckets)
 */
class Renderer
{
public:
	/**
	 * Initializes GPU resources (VAOs, VBOs, shaders, states).
	 */
	void Init();

	void RenderWorld(World* world, glm::vec2 viewportBaseResolution, glm::vec2 windowSize);
	
private:
	/**
	 * Initializes vertex data (quad + text geometry).
	 */
	void InitRenderData();

	void RenderScene(RenderBucket& buckets, CameraComponent* camera, glm::vec2 viewportBaseResolution);
	void RenderUI(std::vector<RenderItem*>& uiItems, glm::vec2 windowSize);

	/**
	 * Renders a material using given transformation matrices.
	 */
	void RenderMaterial(RenderTextureItem* item, glm::mat4 view, glm::mat4 projection);
	
	/**
	 * Binds a texture and renders a quad.
	 */
	void DrawTexture(Texture* texture);
	
	/**
	 * Renders a text element glyph by glyph.
	 */
	void RenderText(RenderTextItem* textItem, glm::mat4 projection);

	unsigned int quadVAO = 0;
	unsigned int textVAO = 0;
	unsigned int textVBO = 0;

	Shader* textShader = nullptr;
};

#endif // __RENDERER_H_INCLUDED__