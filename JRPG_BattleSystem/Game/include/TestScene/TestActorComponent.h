#ifndef __TEST_ACTOR_COMPONENT_INCLUDED__
#define __TEST_ACTOR_COMPONENT_INCLUDED__

#include "Components/ActorComponent.h"

class TestActorComponent : public ActorComponent
{
public:
	void BeginPlay() override;
};

#endif // __TEST_ACTOR_COMPONENT_INCLUDED__