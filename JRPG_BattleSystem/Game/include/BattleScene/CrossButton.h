#ifndef __CROSS_BUTTON_H_INCLUDED__
#define __CROSS_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class CrossButton : public Button
{
public:
	CrossButton(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));

	void OnClicked() override;
};

#endif // __CROSS_BUTTON_H_INCLUDED__