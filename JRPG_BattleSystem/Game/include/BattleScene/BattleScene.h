#ifndef __BATTLE_SCENE_H_INCLUDED__
#define __BATTLE_SCENE_H_INCLUDED__

#include "Scene/Scene.h"

class BattleScene : public Scene
{
public:
	void LoadAssets() override;
	void CreateScene() override;
};

#endif // __BATTLE_SCENE_H_INCLUDED__