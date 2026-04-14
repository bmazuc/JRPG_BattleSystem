#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

class Shader;
class Sprite;

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

class Renderer
{
public:
	~Renderer();

	void InitShader(const char* vShaderFile, const char* fShaderFile);
	void InitRenderData(glm::vec2 viewportBaseResolution);

	void RenderSprite(Sprite* sprite, SDL_Window* window);

private:
	Shader* shader;
	unsigned int quadVAO;
};

#endif // __RENDERER_H_INCLUDED__