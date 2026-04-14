#ifndef __SPRITE_RENDERER_H_INCLUDED__
#define __SPRITE_RENDERER_H_INCLUDED__

class Shader;
class Sprite;

#include <SDL3/SDL.h>
#include <vector>
#include <glm/vec2.hpp>

class SpriteRenderer
{
public:
	~SpriteRenderer();

	void InitShader(const char* vShaderFile, const char* fShaderFile);
	void InitRenderData(glm::vec2 viewportBaseResolution);

	void Render(SDL_Window* window);

	void AddSprite(Sprite* sprite) { sprites.push_back(sprite); }

private:
	void RenderSprite(Sprite* sprite, SDL_Window* window);

	Shader* shader;
	unsigned int quadVAO;
	std::vector<Sprite*> sprites;
};

#endif // __SPRITE_RENDERER_H_INCLUDED__