#ifndef __RETURN_BUTTON_H_INCLUDED__
#define __RETURN_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class ReturnButton : public Button
{
public:
	ReturnButton(std::string textureName, std::string shaderName, glm::vec3 color = glm::vec3(1, 1, 1));

	void OnClicked() override;
};

#endif // __RETURN_BUTTON_H_INCLUDED__