#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

class Texture;
class Shader;

#include <glm/vec3.hpp>
#include <string>

class Material
{
public:
	Material(std::string textureName, std::string shaderName, glm::vec3 _color);

	glm::vec3 GetColor() const { return color; }
	Shader* GetShader() const { return shader; }
	Texture* GetTexture() const { return texture; }

private:
	glm::vec3 color = glm::vec3(1, 1, 1);

	Texture* texture;
	Shader* shader;
};

#endif