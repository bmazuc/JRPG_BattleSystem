#include "Scene/ObjectCollections/ComponentCollection.h"

void ComponentCollection::BeginPlay()
{
    Iterate([](ActorComponent* component)
        {
            component->BeginPlay();
        });
}

void ComponentCollection::Update(float deltaTime)
{
    Iterate([deltaTime](ActorComponent* component)
        {
            component->Update(deltaTime);
        });
}

void ComponentCollection::InitObject(ActorComponent* component)
{
    component->BeginPlay();
}