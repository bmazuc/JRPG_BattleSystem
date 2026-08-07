#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

class Texture;
class Shader;

#include <glm/vec4.hpp>
#include <string>

/**
 * Defines how a surface is rendered.
 * A material stores the rendering resources and visual parameters required to draw an object.
 */
class Material
{
public:
	Material();

	/**
	 * Creates a material using the specified resources.
	 *
	 * @param textureName Texture resource name.
	 * @param shaderName Shader resource name.
	 * @param _color Tint color applied during rendering.
	 */
	Material(std::string textureName, std::string shaderName, glm::vec4 _color);

	glm::vec4 GetColor() const { return color; }

	Shader* GetShader() { return shader; }
	const Shader* GetShader() const { return shader; }

	Texture* GetTexture() { return texture; }
	const Texture* GetTexture() const { return texture; }

	void SetColor(glm::vec4 newColor) { color = newColor; }
	void SetShader(std::string name);
	void SetTexture(std::string name);

private:
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Texture* texture = nullptr;
	Shader* shader = nullptr;
};

#endif