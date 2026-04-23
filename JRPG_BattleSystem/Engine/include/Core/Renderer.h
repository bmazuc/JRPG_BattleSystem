#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

class Shader;
class SpriteRendererComponent;
class Scene;

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include <map>
#include <vector>

class Renderer
{
public:
	~Renderer();

	void Init(const char* vShaderFile, const char* fShaderFile, glm::vec2 viewportBaseResolution);

	void Render(Scene* scene, SDL_Window* window);

private:
	void InitRenderData(glm::vec2 viewportBaseResolution);

	void Build(Scene* scene);
	void DrawSprite(SpriteRendererComponent* sprite, SDL_Window* window);

	Shader* shader;
	unsigned int quadVAO;

	std::map<int, std::vector<SpriteRendererComponent*>> buckets;
};

#endif // __RENDERER_H_INCLUDED__