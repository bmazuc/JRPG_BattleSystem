#include "BattleScene/CrossButton.h"

CrossButton::CrossButton(std::string textureName, std::string shaderName, glm::vec3 color)
	: Button(textureName, shaderName, color)
{
}

void CrossButton::OnClicked()
{
	Destroy(true);
}
