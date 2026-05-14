#ifndef __UI_ELEMENT_COLLECTION_H_INCLUDED__
#define __UI_ELEMENT_COLLECTION_H_INCLUDED__

#include "ObjectCollection.h"
#include "UI/UIElement.h"

/**
 * Collection specialized for UI elements.
 * Handles UI lifecycle and input-driven updates.
 */
class UIElementCollection : public ObjectCollection<UIElement>
{
public:
	void BeginPlay();
	void Update(float deltaTime);

private:
	void InitObject(UIElement* element) override;
	void BeginDestroyObject(UIElement* element) override;
};

#endif // __UI_ELEMENT_COLLECTION_H_INCLUDED__