#ifndef __LOAD_SCENE_BUTTON_INCLUDED__
#define __LOAD_SCENE_BUTTON_INCLUDED__

#include "UI/Button.h"
#include <string>

class LoadSceneButton : public Button
{
public:
	void OnClicked() override;

	void SetSceneToLoad(std::string sceneName) { sceneToLoad = sceneName; }
	std::string GetSceneToLoad() const { return sceneToLoad; }

private:
	std::string sceneToLoad;
};

#endif // __LOAD_SCENE_BUTTON_INCLUDED__