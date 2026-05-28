#ifndef __SWITCH_Z_ORDER_BUTTON_H_INCLUDED__
#define __SWITCH_Z_ORDER_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class SwitchZOrderButton : public Button
{
public:
	void OnClicked() override;
	void SetWidget(Widget* newWidget) { widget = newWidget; }

private:
	Widget* widget;
};

#endif // __SWITCH_Z_ORDER_BUTTON_H_INCLUDED__