#ifndef __BUTTON_H_INCLUDED__
#define __BUTTON_H_INCLUDED__

#include "Image.h"

class Button : public Image
{
public:
	Button(std::string textureName = "default", std::string shaderName = "default", glm::vec3 color = glm::vec3(1,1,1));

	bool IsPointInside(glm::vec2 point) const;

	virtual void OnHover() {}
	virtual void OnClicked() 
	{
	
	}
};

#endif // __BUTTON_H_INCLUDED__