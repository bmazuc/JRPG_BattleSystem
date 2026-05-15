#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

class SpriteRendererComponent;
class Scene;
class Texture;
class Image;
class Material;
class Text;
class Shader;

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <map>
#include <vector>

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
	~Renderer();

	/**
	 * Initializes GPU resources (VAOs, VBOs, shaders, states).
	 */
	void Init();

	/**
	 * Renders the 2D world content of a scene.
	 *
	 * @param scene Scene to render.
	 * @param viewportBaseResolution Reference resolution for projection.
	 */
	void RenderWorld(Scene* scene, glm::vec2 viewportBaseResolution);
	
	/**
	 * Renders widgets of a scene.
	 *
	 * @param scene Scene to render.
	 * @param windowSize Current window resolution.
	 */
	void RenderUI(Scene* scene, glm::vec2 windowSize);
	
private:
	/**
	 * Initializes vertex data (quad + text geometry).
	 */
	void InitRenderData();

	/**
	 * Builds render batches (sorted by z-order).
	 * @param scene Scene used to collect renderable components.
	 */
	void Build(Scene* scene);

	/**
	 * Renders a material using given transformation matrices.
	 */
	void RenderMaterial(Material* material, glm::mat4 view, glm::mat4 model, glm::mat4 projection);
	
	/**
	 * Binds a texture and renders a quad.
	 */
	void DrawTexture(Texture* texture);
	
	/**
	 * Renders a text element glyph by glyph.
	 */
	void RenderText(Text* text, glm::mat4 projection);

	unsigned int quadVAO = 0;
	unsigned int textVAO = 0;
	unsigned int textVBO = 0;

	Shader* textShader = nullptr;

	// Render buckets grouped by z-order (used for ordering sprites).
	std::map<int, std::vector<SpriteRendererComponent*>> buckets;
};

#endif // __RENDERER_H_INCLUDED__