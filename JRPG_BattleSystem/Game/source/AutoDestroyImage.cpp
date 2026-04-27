#include "AutoDestroyImage.h"

AutoDestroyImage::AutoDestroyImage(std::string textureName, std::string shaderName, glm::vec3 color)
    : Image(textureName, shaderName, color)
{  
}

void AutoDestroyImage::Update(float deltaTime)
{
	timer += deltaTime;

    if (timer >= 6)
    {
        // Destroy should not be called twice but I do it to check if it crashes.
        Destroy();
        Destroy();
    }
}