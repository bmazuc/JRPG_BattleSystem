#include "SwitchZOrderButton.h"

void SwitchZOrderButton::OnClicked()
{
	if (!widget)
	{
		return;
	}

	int currentZOrder = widget->GetZOrder();

	if (currentZOrder == 0)
	{
		widget->SetZOrder(1);
	}
	else
	{
		widget->SetZOrder(0);
	}
}