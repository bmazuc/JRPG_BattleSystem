#include "BattleLevel/UI/DamageDisplayer.h"

void DamageDisplayer::Display(int damageTaken)
{
	SetContent(std::to_string(damageTaken));
}