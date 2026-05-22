#include "World/ObjectCollections/ComponentCollection.h"

void ComponentCollection::BeginPlay()
{
    InitObject([](ActorComponent* component)
        {
            component->BeginPlay();
        });
}

void ComponentCollection::Update(float deltaTime)
{
    ForEach([deltaTime](ActorComponent* component)
        {
            component->Update(deltaTime);
        });
}

void ComponentCollection::BeginDestroyObject(ActorComponent* component)
{
    component->NativeBeginDestroy();
}