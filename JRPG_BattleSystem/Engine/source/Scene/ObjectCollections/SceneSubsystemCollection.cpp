#include "Scene/ObjectCollections/SceneSubsystemCollection.h"

void SceneSubsystemCollection::BeginPlay()
{
    Iterate([](SceneSubsystem* subsystem)
        {
            subsystem->Initialize();
        });
}

void SceneSubsystemCollection::Update(float deltaTime)
{
    Iterate([deltaTime](SceneSubsystem* subsystem)
        {
            subsystem->Update(deltaTime);
        });
}

void SceneSubsystemCollection::InitObject(SceneSubsystem* subsystem)
{
    subsystem->Initialize();
}

void SceneSubsystemCollection::BeginDestroyObject(SceneSubsystem* subsystem)
{
    subsystem->Deinitialize();
}