#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

class Material;

#include "Rendering/Shader.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

class Sprite
{
public:
	Sprite(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));
	~Sprite();

	Material* GetMaterial() const { return material; }

	glm::vec2 GetSize() const { return size; }
	int GetLayer() const { return layer; }

	void SetSize(glm::vec2 _size) { size = _size; }
	void SetLayer(int _layer) { layer = _layer; }

private:
	glm::vec2 size = glm::vec2(1, 1); 

	int layer = 0;

	Material* material;
};

#endif // __SPRITE_H_INCLUDED__