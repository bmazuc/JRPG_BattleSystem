#include "UI/Button.h"

Button::Button(std::string textureName, std::string shaderName, Color color)
    : Image(textureName, shaderName, color)
{
}

bool Button::IsPointInside(glm::vec2 point) const
{
    glm::vec2 bounds = size * GetWorldScale();
    bounds /= 2.0f;
    glm::vec2 worldPos = GetWorldPosition();

    return point.x >= worldPos.x - bounds.x &&
        point.x <= worldPos.x + bounds.x &&
        point.y >= worldPos.y - bounds.y &&
        point.y <= worldPos.y + bounds.y;
}