#include "TestScene/CrossButton.h"

void CrossButton::OnClicked()
{
	MarkForDestruction(true);
}
