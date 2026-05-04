#ifndef __START_BUTTON_H_INCLUDED__
#define __START_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class StartButton : public Button
{
public:
	void OnClicked() override;
};

#endif // __START_BUTTON_H_INCLUDED__