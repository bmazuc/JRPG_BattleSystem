#include "Scene/Actor.h"
#include "Scene/Scene.h"

Actor::Actor()
{
	root = AddComponent<Component>(name + " root", nullptr, glm::vec2(0, 0), 0, glm::vec2(1,1));
}

Actor::~Actor()
{
	componentsCollection.Clear();
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

void Actor::ComponentsBeginPlay()
{
	componentsCollection.BeginPlay();
}

void Actor::UpdateComponents(float deltaTime)
{
	componentsCollection.Update(deltaTime);
}

void Actor::ProcessComponentsDestroy()
{
	componentsCollection.ProcessDestroy();
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

void Actor::Destroy(bool destroyChildren)
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		scene->RegisterToDestroy(this);

		if (destroyChildren)
		{
			std::vector<Component*> children = root->GetChildren();
			for (Component* child : children)
			{
				if (child->GetOwner() != this)
				{
					child->GetOwner()->Destroy(true);
				}
			}
		}
	}
}

void Actor::RegisterComponentsToDestroy(Component* component)
{
	componentsCollection.RegisterToDestroy(component);
}

Actor* Actor::GetParent()
{ 
	return root->HasParent() ? root->GetParent()->GetOwner() : nullptr; 
}

const Actor* Actor::GetParent() const
{ 
	return root->HasParent() ? root->GetParent()->GetOwner() : nullptr; 
}

void Actor::DetachFromHierarchy()
{
	root->DetachFromHierarchy();
}