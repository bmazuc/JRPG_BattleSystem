#include "ChangeSceneTimer.h"
#include "Scene/Scene.h"

ChangeSceneTimer::ChangeSceneTimer(std::string fontName, bool isCenter, glm::vec3 _color)
    : Text(fontName, isCenter, _color)
{

}

void ChangeSceneTimer::Update(float deltaTime)
{
    timer += deltaTime;

    SetContent(std::to_string(int(6 - timer)));

    if (timer >= 6)
    {
        GetScene()->RequestSceneChange("battleScene");
    }
}