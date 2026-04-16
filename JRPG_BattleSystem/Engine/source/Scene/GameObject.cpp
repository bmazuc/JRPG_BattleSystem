#include "Scene/GameObject.h"
#include "Components/Component.h"

GameObject::~GameObject()
{
	for (Component* component : components)
	{
		delete component;
	}

	components.clear();
}