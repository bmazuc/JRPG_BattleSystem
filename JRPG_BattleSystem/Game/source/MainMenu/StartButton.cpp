#include "MainMenu/StartButton.h"
#include "Scene/Scene.h"

StartButton::StartButton(std::string textureName, std::string shaderName, glm::vec3 color)
	: Button(textureName, shaderName, color)
{
}

void StartButton::OnClicked()
{
	GetScene()->RequestSceneChange("battleScene");
}