#ifndef __CHANGE_SCENE_TIMER_H_INCLUDED
#define __CHANGE_SCENE_TIMER_H_INCLUDED

#include "UI/Text.h"

class ChangeSceneTimer : public Text
{
public:
	ChangeSceneTimer(std::string fontName, bool isCenter = true, glm::vec3 _color = glm::vec3(1, 1, 1));

	void Update(float deltaTime) override;

private:
	float timer = 0.0f;
};

#endif // __CHANGE_SCENE_TIMER_H_INCLUDED