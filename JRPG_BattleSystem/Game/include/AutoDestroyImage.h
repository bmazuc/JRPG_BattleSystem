#ifndef __AUTO_DESTROY_IMAGE_H_INCLUDED__
#define __AUTO_DESTROY_IMAGE_H_INCLUDED__

#include "UI/Image.h"
#include <string>

class AutoDestroyImage : public Image
{
public:
	AutoDestroyImage(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));

	void Update(float deltaTime) override;

private:
	float timer = 0.0f;
};

#endif // __AUTO_DESTROY_IMAGE_H_INCLUDED__