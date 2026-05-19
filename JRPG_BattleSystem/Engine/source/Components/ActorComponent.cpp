#include "Components/ActorComponent.h"
#include "World/Level/Scene/Actor.h"

void ActorComponent::NativeBeginDestroy()
{
	BeginDestroy();
}

void ActorComponent::MarkForDestruction()
{ 
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		if (owner)
		{
			owner->RegisterComponentsToDestroy(this);
		}
	}
}

