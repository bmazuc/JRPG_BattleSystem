#ifndef __START_BUTTON_H_INCLUDED__
#define __START_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class StartButton : public Button
{
public:
	StartButton(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));

	void OnClicked() override;
};

#endif // __START_BUTTON_H_INCLUDED__