#ifndef __LOAD_LEVEL_BUTTON_INCLUDED__
#define __LOAD_LEVEL_BUTTON_INCLUDED__

#include "UI/Button.h"
#include <string>

class LoadLevelButton : public Button
{
public:
	void OnClicked() override;

	void SetLevelToLoad(std::string nextLevelName) { levelToLoad = nextLevelName; }
	std::string GetLevelToLoad() const { return levelToLoad; }

private:
	std::string levelToLoad;
};

#endif // __LOAD_LEVEL_BUTTON_INCLUDED__