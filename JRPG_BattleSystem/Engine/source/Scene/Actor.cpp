#include "Scene/Actor.h"
#include "Components/Component.h"
#include "Scene/Scene.h"

Actor::Actor()
{
	root = AddComponent<Component>();
}

Actor::~Actor()
{
	for (Component* component : components)
	{
		delete component;
	}

	components.clear();
}

void Actor::AttachToActor(Actor* actor)
{
	if (actor)
	{
		root->SetParent(actor->GetRoot());
	}
}

void Actor::Detach()
{
	root->SetParent(nullptr);
}

void Actor::UpdateTransforms()
{
	if (root)
	{
		root->UpdateTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (Component* component : components)
	{
		if (component)
		{
			component->Update(deltaTime);
		}
	}
}

void Actor::ProcessComponentsDestroy()
{
	for (Component* componentToDestroy : componentsToDestroy)
	{
		if (componentToDestroy)
		{
			components.erase(std::remove(components.begin(), components.end(), componentToDestroy), components.end());
			delete componentToDestroy;
		}
	}

	componentsToDestroy.clear();
}

glm::vec2 Actor::GetLocalPosition() const
{
	return root ? root->GetLocalPosition() : glm::vec2();
}

float Actor::GetLocalRotate() const
{
	return root ? root->GetLocalRotate() : 0.0f;
}

glm::vec2 Actor::GetLocalScale() const
{
	return root ? root->GetLocalScale() : glm::vec2();
}

void Actor::SetLocalPosition(glm::vec2 position)
{
	if (root)
	{
		root->SetLocalPosition(position);
	}
}

void Actor::SetLocalRotate(float rotate)
{
	if (root)
	{
		root->SetLocalRotate(rotate);
	}
}

void Actor::SetLocalScale(glm::vec2 scale)
{
	if (root)
	{
		root->SetLocalScale(scale);
	}
}

glm::vec2 Actor::GetWorldPosition() const
{
	return root ? root->GetWorldPosition() : glm::vec2();
}

float Actor::GetWorldRotate() const
{
	return root ? root->GetWorldRotate() : 0.0f;
}

glm::vec2 Actor::GetWorldScale() const
{
	return root ? root->GetWorldScale() : glm::vec2();
}

void Actor::SetWorldPosition(glm::vec2 position)
{
	if (root)
	{
		root->SetWorldPosition(position);
	}
}

void Actor::SetWorldRotate(float rotate)
{
	if (root)
	{
		root->SetWorldRotate(rotate);
	}
}

void Actor::SetWorldScale(glm::vec2 scale)
{
	if (root)
	{
		root->SetWorldScale(scale);
	}
}

void Actor::Destroy()
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		scene->RegisterToDestroy(this);
	}
}

void Actor::RegisterComponentsToDestroy(Component* component)
{
	componentsToDestroy.push_back(component);
}