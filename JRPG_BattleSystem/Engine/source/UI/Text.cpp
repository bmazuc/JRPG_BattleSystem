#include "UI/Text.h"
#include "Core/Resource/ResourceManager.h"

Text::Text(std::string fontName, bool _isCenter, glm::vec4 _color)
	: isCenterX(_isCenter), color(_color)
{
	font = &ResourceManager::GetFont(fontName);
}

void Text::SetFont(std::string fontName)
{
	font = &ResourceManager::GetFont(fontName);
}

void Text::AddToRenderQueue(RenderQueue& queue)
{
	if (GetNode()->IsEffectivelyVisible())
	{
		queue.AddUIItem(new RenderTextItem(GetTransform().world, size, content, font, color, scaleMode, isCenterX));
	}
}