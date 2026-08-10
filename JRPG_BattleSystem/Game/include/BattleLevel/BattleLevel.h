#ifndef __BATTLE_LEVEL_H_INCLUDED__
#define __BATTLE_LEVEL_H_INCLUDED__

#include "World/Level/Level.h"

class BattleManager;
class UISystem;

class BattleLevel : public Level
{
public:
	void LoadAssets() override;
	void CreateLevel() override;

private:
	BattleManager* CreateBattleManager();
	void CreateBattleUI(BattleManager* battleManager, UISystem* uiSystem);
};

#endif // __BATTLE_SCENE_LEVEL_H_INCLUDED__