#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

#include "Texture.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Sprite
{
public:
	~Sprite();

	void LoadBMP(const char* file);
	void LoadPNG(const char* file);

	Texture* GetTexture() const { return texture; }

	glm::vec2 GetPosition() const { return position; }
	float GetRotate() const { return rotate; }
	glm::vec2 GetSize() const { return size; }
	glm::vec3 GetColor() const { return color; }

	void SetPosition(glm::vec2 _position) { position = _position; }
	void SetRotate(float _rotate) { rotate = _rotate; }
	void SetSize(glm::vec2 _size) { size = _size; }
	void SetColor(glm::vec3 _color) { color = _color; }

private:
	glm::vec2 position = glm::vec2(0, 0);
	float rotate = 0;
	glm::vec2 size = glm::vec2(1, 1); 
	glm::vec3 color = glm::vec3(1, 1, 1);

	Texture* texture;
};

#endif // __SPRITE_H_INCLUDED__