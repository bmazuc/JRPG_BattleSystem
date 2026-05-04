#ifndef __CROSS_BUTTON_H_INCLUDED__
#define __CROSS_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class CrossButton : public Button
{
public:
	void OnClicked() override;
};

#endif // __CROSS_BUTTON_H_INCLUDED__