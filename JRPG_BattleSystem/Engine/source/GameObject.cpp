#include "GameObject.h"
#include "Component.h"

GameObject::~GameObject()
{
	for (Component* component : components)
	{
		delete component;
	}

	components.clear();
}