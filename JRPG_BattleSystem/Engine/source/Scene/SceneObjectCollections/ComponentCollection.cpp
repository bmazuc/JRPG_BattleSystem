#include "Scene/SceneObjectCollections/ComponentCollection.h"

void ComponentCollection::BeginPlay()
{
    Iterate([](Component* component)
        {
            component->BeginPlay();
        });
}

void ComponentCollection::Update(float deltaTime)
{
    Iterate([deltaTime](Component* component)
        {
            component->Update(deltaTime);
        });
}

void ComponentCollection::InitObject(Component* component)
{
    component->BeginPlay();
}