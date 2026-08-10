#ifndef __COUNTDOWN_WIDGET_H_INCLUDED__
#define __COUNTDOWN_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"
#include "Core/Delegate/Delegate.h"

class Text;

class CountdownWidget : public UserWidget
{
public:
	void Construct() override;
	void Update(float deltaTime) override;

	void SetCount(int InCount) { count = InCount; }
	// How many time should elapsed between two numbers ?
	void SetInBetweenCountDuration(float _inBetweenCountDuration) { inBetweenCountDuration = _inBetweenCountDuration; }
	
	Delegate<void> OnCountdownEnd;

private:
	Text* countdownText;

	int count = 3;
	float timer = 0.0f;
	float inBetweenCountDuration = 1.0f;
};

#endif // __COUNTDOWN_WIDGET_H_INCLUDED__