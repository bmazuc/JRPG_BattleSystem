#ifndef __BATTLE_WIDGET_H_INCLUDED__
#define __BATTLE_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"

enum class TurnType;

class Text;
class Scene;

struct DamageDisplayTextData
{
public:
	DamageDisplayTextData(Text* _text) : text(_text) {}

	Text* text;
	float lifeTime = 0.0f;
};

class BattleWidget : public UserWidget
{
public:
	void Construct() override;

	void Update(float deltaTime) override;

	void SetTurnText(TurnType turnType);
	void SetCurrentScene(Scene* scene) { currentScene = scene; }
	void SetDamageTextDuration(float duration) { damageTextDuration = duration; }
	void SetDamageTextSpeed(float speed) { damageTextSpeed = speed; }

	void DisplayDamage(glm::vec2 worldPosition, int damageTaken);

	Delegate<void> OnAllDamageTextDestroy;

private:
	Text* turnText;
	Scene* currentScene;

	std::vector<DamageDisplayTextData> currentDamageTextDisplayed;

	TurnType currentTurnType;

	float damageTextDuration = 1.0f;
	float damageTextSpeed = 30.0f;
};
 
#endif // __BATTLE_WIDGET_H_INCLUDED__