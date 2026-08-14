#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

class Texture;
class Shader;

#include "Rendering/Color.h"
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
	Material(std::string textureName, std::string shaderName, Color _color);

	Color GetColor() const { return color; }

	Shader* GetShader() { return shader; }
	const Shader* GetShader() const { return shader; }

	Texture* GetTexture() { return texture; }
	const Texture* GetTexture() const { return texture; }

	void SetColor(Color newColor) { color = newColor; }
	void SetShader(std::string name);
	void SetTexture(std::string name);

private:
	Color color = Colors::White;

	Texture* texture = nullptr;
	Shader* shader = nullptr;
};

#endif