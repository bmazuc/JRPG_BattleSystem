#include "World/Level/Scene/Actor.h"
#include "World/Level/Scene/Scene.h"
#include "Components/SceneComponent.h"

Actor::Actor()
{
	root = SpawnSceneComponent<SceneComponent>(name + "Root", SceneComponentSpawnInfo());
}

Actor::~Actor()
{
	componentsCollection.Clear();
}

void Actor::SetScene(Scene* newScene)
{
	scene = newScene;
	if (scene)
	{
		if (!root->GetParent())
		{
			scene->GetSceneGraph()->AddNode(root->GetSceneNode());
		}
	}
}

void Actor::AttachToActor(Actor* actor)
{
	if (!root->GetParent() && actor)
	{
		scene->GetSceneGraph()->RemoveNode(root->GetSceneNode());
	}
	else if (root->GetParent() && !actor)
	{
		scene->GetSceneGraph()->AddNode(root->GetSceneNode());
	}

	root->SetParent(actor ? actor->GetRoot() : nullptr);
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

void Actor::ProcessComponentsAdd()
{
	componentsCollection.FlushPendingAdds();
}

void Actor::ProcessComponentsDestroy()
{
	componentsCollection.FlushPendingDestroys();
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

void Actor::NativeBeginDestroy()
{
	DetachFromHierarchy();
	BeginDestroy();
}

void Actor::MarkForDestruction(bool markChildren)
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		scene->RegisterToDestroy(this);

		if (markChildren)
		{
			std::vector<SceneComponent*> children = root->GetChildren();
			for (SceneComponent* child : children)
			{
				if (child->GetOwner() != this)
				{
					child->GetOwner()->MarkForDestruction(true);
				}
			}
		}
	}
}

void Actor::RegisterComponentsToDestroy(ActorComponent* component)
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
	scene->GetSceneGraph()->RemoveNode(root->GetSceneNode());
}

void Actor::InternalSpawnSceneComponent(SceneComponent* component, const SceneComponentSpawnInfo& spawnInfo)
{
	component->SetParent(spawnInfo.parent ? spawnInfo.parent : root);

	if (spawnInfo.transformSpace == TransformSpace::World)
	{
		component->SetWorldPosition(spawnInfo.location);
		component->SetWorldRotate(spawnInfo.rotate);
		component->SetWorldScale(spawnInfo.scale);
	}
	else
	{
		component->SetLocalPosition(spawnInfo.location);
		component->SetLocalRotate(spawnInfo.rotate);
		component->SetLocalScale(spawnInfo.scale);
	}
}

void Actor::RegisterComponent(ActorComponent* component, std::string name)
{
	component->SetOwner(this);
	component->SetName(name);

	componentsCollection.RegisterToAdd(component);
}