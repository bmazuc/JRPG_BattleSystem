#ifndef __GAME_OVER_WIDGET_H_INCLUDED__
#define __GAME_OVER_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"

class Text;

/**
 * Defines the game over screen, including its UI composition, layout, and appearance.
 *
 * This widget encapsulates the construction and visual configuration of its
 * UI elements. Gameplay-specific data is supplied through its public interface.
 */
class GameOverWidget : public UserWidget
{
public:
	void Construct() override;

	void SetKillCount(int killCount);

private:
	Text* text;
};

#endif // __GAME_OVER_WIDGET_H_INCLUDED__