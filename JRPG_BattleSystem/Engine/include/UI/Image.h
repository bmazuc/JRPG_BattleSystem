#ifndef __IMAGE_H_INCLUDED__
#define __IMAGE_H_INCLUDED__

#include "UIElement.h"

#include "Graphics/Texture.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Image : public UIElement
{
public:
	~Image();

	void LoadBMP(const char* file);
	void LoadPNG(const char* file);

	Texture* GetTexture() const { return texture; }

	glm::vec2 GetSize() const { return size; }
	glm::vec3 GetColor() const { return color; }

	void SetSize(glm::vec2 _size) { size = _size; }
	void SetColor(glm::vec3 _color) { color = _color; }

private:
	glm::vec2 size = glm::vec2(1, 1);
	glm::vec3 color = glm::vec3(1, 1, 1);

	Texture* texture;
};

#endif // __IMAGE_H_INCLUDED__