#ifndef __MAIN_MENU_LEVEL_H_INCLUDED__
#define __MAIN_MENU_LEVEL_H_INCLUDED__

#include "World/Level/Level.h"

class UserWidget;

class MainMenuLevel : public Level
{
public:
	void LoadAssets() override;
	void CreateLevel() override;

private:
	void CreateLoadLevelButton(glm::vec2 position, glm::vec2 buttonSize, std::string levelToLoad, std::string content, float textSize);

	UserWidget* mainMenuWidget = nullptr;
};

#endif // __MAIN_MENU_LEVEL_H_INCLUDED__