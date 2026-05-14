#include "Components/ActorComponent.h"
#include "Scene/Actor.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

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

