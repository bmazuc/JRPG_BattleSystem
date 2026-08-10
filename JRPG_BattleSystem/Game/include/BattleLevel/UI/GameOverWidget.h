#ifndef __GAME_OVER_WIDGET_H_INCLUDED__
#define __GAME_OVER_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"

class Text;

class GameOverWidget : public UserWidget
{
public:
	void Construct() override;

	void SetKillCount(int killCount);

private:
	Text* text;
};

#endif // __GAME_OVER_WIDGET_H_INCLUDED__