#include "World/ObjectCollections/LevelSubsystemCollection.h"

void LevelSubsystemCollection::BeginPlay()
{
    Iterate([](LevelSubsystem* subsystem)
        {
            subsystem->Initialize();
        });
}

void LevelSubsystemCollection::Update(float deltaTime)
{
    Iterate([deltaTime](LevelSubsystem* subsystem)
        {
            subsystem->Update(deltaTime);
        });
}

void LevelSubsystemCollection::InitObject(LevelSubsystem* subsystem)
{
    subsystem->Initialize();
}

void LevelSubsystemCollection::BeginDestroyObject(LevelSubsystem* subsystem)
{
    subsystem->Deinitialize();
}