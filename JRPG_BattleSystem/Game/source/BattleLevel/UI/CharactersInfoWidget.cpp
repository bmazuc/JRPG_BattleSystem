#include "BattleLevel/UI/CharactersInfoWidget.h"
#include "UI/Image.h"

void CharactersInfoWidget::Construct()
{
	Image* background = CreateWidget<Image>("InfosBackground", UISpawnInfo(nullptr, TransformSpace::Local));
}