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

/*
 *	Core rendering system base on OpenGL.
 */
class Renderer
{
public:
	~Renderer();

	// Initialize renderer (VAO, text shader, blending)
	void Init();

	// To upgrade make a render command system

	/*
	 *	Render all actors in a scene.
	 *	@param scene the scene to render
	 *	@param viewportBaseResolution the initial resolution set to the window
	 */
	void RenderWorld(Scene* scene, glm::vec2 viewportBaseResolution);
	/*
	 *	Render all UI elements in a scene.
	 *	@param scene the scene to render
	 *	@param windowSize the current resolution of the window
	 */
	void RenderUI(Scene* scene, glm::vec2 windowSize);
	
private:
	/*
	*	Generate quad and text VAO and VBO
	*/
	void InitRenderData();

	/*
	 *	Create rendering buckets.
	 *	@param scene the scene to render
	 */
	void Build(Scene* scene);

	/*
	 *	Render a material.
	 *	@param material the material to render
	 *	@param view the view matrice
	 *	@param model the model matrice
	 *	@param projection the projection matrice
	 */
	void RenderMaterial(Material* material, glm::mat4 view, glm::mat4 model, glm::mat4 projection);
	/*
	 *	Bind a texture then draw a quad.
	 *	@param texture the texture to bind
	 */
	void DrawTexture(Texture* texture);
	/*
	 *	Render text, glyph by glyph
	 *	@param text the text to render
	 *	@param projection projection matrice
	 */
	void RenderText(Text* text, glm::mat4 projection);

	unsigned int quadVAO;
	unsigned int textVAO;
	unsigned int textVBO;

	Shader* textShader;

	std::map<int, std::vector<SpriteRendererComponent*>> buckets;
};

#endif // __RENDERER_H_INCLUDED__