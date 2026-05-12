#ifndef __COMPONENT_COLLECTION_H_INCLUDED__
#define __COMPONENT_COLLECTION_H_INCLUDED__

#include "ObjectCollection.h"
#include "Components/Component.h"

/**
 * Collection specialized for Component objects.
 * Minimal extension of ObjectCollection, used mainly for lifecycle hooks.
 */
class ComponentCollection : public ObjectCollection<Component>
{
public:
	void BeginPlay();
	void Update(float deltaTime);

private:
	void InitObject(Component* actor) override;
};

#endif // __COMPONENT_COLLECTION_H_INCLUDED__