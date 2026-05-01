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

class Renderer
{
public:
	~Renderer();

	void Init();

	// To upgrade make a render command system
	void RenderWorld(Scene* scene, glm::vec2 viewportBaseResolution);
	void RenderUI(Scene* scene, glm::vec2 windowSize);
	
private:
	void InitRenderData();

	void Build(Scene* scene);

	void RenderMaterial(Material* material, glm::mat4 view, glm::mat4 model, glm::mat4 projection);
	void DrawTexture(Texture* texture);

	void RenderText(Text* text, glm::mat4 projection);

	unsigned int quadVAO;
	unsigned int textVAO;
	unsigned int textVBO;

	Shader* textShader;

	std::map<int, std::vector<SpriteRendererComponent*>> buckets;
};

#endif // __RENDERER_H_INCLUDED__