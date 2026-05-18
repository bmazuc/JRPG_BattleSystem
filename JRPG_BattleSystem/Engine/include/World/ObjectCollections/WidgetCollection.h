#ifndef __UI_ELEMENT_COLLECTION_H_INCLUDED__
#define __UI_ELEMENT_COLLECTION_H_INCLUDED__

#include "ObjectCollection.h"
#include "UI/Widget.h"

/**
 * Collection specialized for widgets.
 * Handles UI lifecycle and input-driven updates.
 */
class WidgetCollection : public ObjectCollection<Widget>
{
public:
	void Construct();
	void Update(float deltaTime);

private:
	void InitObject(Widget* widget) override;
	void BeginDestroyObject(Widget* widget) override;
};

#endif // __UI_ELEMENT_COLLECTION_H_INCLUDED__