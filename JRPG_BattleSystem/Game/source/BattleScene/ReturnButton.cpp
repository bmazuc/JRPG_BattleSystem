#include "BattleScene/ReturnButton.h"
#include "Scene/Scene.h"

ReturnButton::ReturnButton(std::string textureName, std::string shaderName, glm::vec3 color)
	: Button(textureName, shaderName, color)
{
}

void ReturnButton::OnClicked()
{
	GetScene()->RequestSceneChange("mainMenu");
}