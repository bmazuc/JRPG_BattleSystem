#include "UI/Text.h"
#include "Core/ResourceManager.h"

Text::Text(std::string fontName, bool _isCenter, glm::vec3 _color)
	: isCenter(_isCenter), color(_color)
{
	font = &ResourceManager::GetFont(fontName);
}

void Text::SetFont(std::string fontName)
{
	font = &ResourceManager::GetFont(fontName);
}