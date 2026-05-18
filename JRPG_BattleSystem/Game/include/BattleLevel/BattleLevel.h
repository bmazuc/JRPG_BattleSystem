#ifndef __BATTLE_LEVEL_H_INCLUDED__
#define __BATTLE_LEVEL_H_INCLUDED__

#include "World/Level.h"

class BattleLevel : public Level
{
public:
	void LoadAssets() override;
	void CreateLevel() override;
};

#endif // __BATTLE_SCENE_LEVEL_H_INCLUDED__