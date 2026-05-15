#ifndef __BUTTON_H_INCLUDED__
#define __BUTTON_H_INCLUDED__

#include "Image.h"

/**
 * Interactive widget based on Image.
 *
 * Button extends Image with input interaction capabilities:
 * - hover detection
 * - click event handling
 *
 * Intended to be overridden for gameplay UI logic.
 */
class Button : public Image
{
public:
	Button(std::string textureName = "default", std::string shaderName = "default", glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

	/**
	 * Checks if a screen-space point is inside the button bounds.
	 */
	bool IsPointInside(glm::vec2 point) const;

	/**
	 * Called when the cursor enters the button area.
	 */
	virtual void OnHover() {}
	/**
	 * Called when the button is clicked.
	 */
	virtual void OnClicked() {}
};

#endif // __BUTTON_H_INCLUDED__