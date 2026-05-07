#ifndef __MAIN_MENU_H_INCLUDED__
#define __MAIN_MENU_H_INCLUDED__

#include "Scene/Scene.h"

class MainMenuScene : public Scene
{
public:
	void LoadAssets() override;
	void CreateScene() override;

private:
	void CreateLoadSceneButton(glm::vec2 position, glm::vec2 buttonSize, std::string sceneToLoad, std::string content, int textSize);
};

#endif // __MAIN_MENU_H_INCLUDED__