#ifndef __COUNTDOWN_WIDGET_H_INCLUDED__
#define __COUNTDOWN_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"
#include "Core/Delegate/Delegate.h"

class Text;

/**
 * Displays a countdown before starting a battle.
 *
 * The countdown decreases at a fixed interval and displays "Start"
 * when it reaches zero.Once the countdown is complete, the widget
 * triggers the OnCountdownEnd event and destroys itself.
 */
class CountdownWidget : public UserWidget
{
public:
	void Construct() override;
	void Update(float deltaTime) override;

	void SetCount(int InCount) { count = InCount; }
	/**
	 * Sets the delay between two countdown values.
	 */
	void SetInBetweenCountDuration(float _inBetweenCountDuration) { inBetweenCountDuration = _inBetweenCountDuration; }
	
	// Event triggered when the countdown reaches its end.
	Delegate<void> OnCountdownEnd;

private:
	Text* countdownText;

	// Current countdown value.
	int count = 3;
	// Time remaining before the next countdown step.
	float timer = 0.0f;
	// Duration between two countdown steps in seconds.
	float inBetweenCountDuration = 1.0f;
};

#endif // __COUNTDOWN_WIDGET_H_INCLUDED__