#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

class Shader;
class SpriteRendererComponent;
class Scene;
class Texture;
class Image;

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <map>
#include <vector>

class Renderer
{
public:
	~Renderer();

	void Init(const char* vShaderFile, const char* fShaderFile, glm::vec2 viewportBaseResolution);

	void RenderWorld(Scene* scene);
	void RenderUI(Scene* scene, SDL_Window* window);

private:
	void InitRenderData(glm::vec2 _viewportBaseResolution);

	void Build(Scene* scene);
	void DrawSprite(SpriteRendererComponent* sprite);
	void DrawImage(Image* image);

	void DrawTexture(Texture* texture, glm::mat4 model, glm::vec2 size, glm::vec3 color);

	glm::vec2 viewportBaseResolution;

	Shader* shader;
	unsigned int quadVAO;

	std::map<int, std::vector<SpriteRendererComponent*>> buckets;
};

#endif // __RENDERER_H_INCLUDED__