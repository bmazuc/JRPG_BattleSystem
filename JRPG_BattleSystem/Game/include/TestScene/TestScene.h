#ifndef __TEST_SCENE_H_INCLUDED__
#define __TEST_SCENE_H_INCLUDED__

#include "Scene/Scene.h"

class TestScene : public Scene
{
public:
	void LoadAssets() override;
	void CreateScene() override;

private:
	void CreateUI();
};

#endif // __TEST_SCENE_H_INCLUDED__