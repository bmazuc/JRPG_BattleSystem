#include "Scene/Actor.h"
#include "Components/Component.h"

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

glm::vec2 Actor::GetPosition() const
{
	return root ? root->GetPosition() : glm::vec2();
}

float Actor::GetRotate() const
{
	return root ? root->GetRotate() : 0.0f;
}

glm::vec2 Actor::GetScale() const
{
	return root ? root->GetScale() : glm::vec2();
}

void Actor::SetPosition(glm::vec2 position)
{
	if (root)
	{
		root->SetPosition(position);
	}
}

void Actor::SetRotate(float rotate)
{
	if (root)
	{
		root->SetRotate(rotate);
	}
}

void Actor::SetScale(glm::vec2 scale)
{
	if (root)
	{
		root->SetScale(scale);
	}
}

void Actor::SetRoot(Component* newRoot) 
{ 
	// Check if changing root doesn't create cyclic references inside graph

	/*if (root)
	{
		if (newRoot && newRoot != root && children > 0)
		{
			//Verifier si root et newroot ne crée des références cycliques
		}
	}*/

	root = newRoot;
}