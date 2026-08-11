#ifndef __BATTLE_WIDGET_H_INCLUDED__
#define __BATTLE_WIDGET_H_INCLUDED__

#include "UI/UserWidget.h"

class Text;
class Scene;
class Image;
class Character;

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

	void InitCharacterInfos(std::vector<Character*> characters);

	void Update(float deltaTime) override;

	void SetTurnText(std::string content);
	void SetCurrentScene(Scene* scene) { currentScene = scene; }
	void SetDamageTextDuration(float duration) { damageTextDuration = duration; }
	void SetDamageTextSpeed(float speed) { damageTextSpeed = speed; }

	void SetInfosBackgroundTexture(std::string textureName) { infosBackgroundTextureName = textureName; }

	void DisplayDamage(glm::vec2 worldPosition, int damageTaken);

	Delegate<void> OnAllDamageTextDestroy;

private:
	Text* turnText;
	Scene* currentScene;
	Image* infosBackground;

	std::vector<DamageDisplayTextData> currentDamageTextDisplayed;

	float damageTextDuration = 1.0f;
	float damageTextSpeed = 30.0f;

	std::string infosBackgroundTextureName = "default";
};
 
#endif // __BATTLE_WIDGET_H_INCLUDED__