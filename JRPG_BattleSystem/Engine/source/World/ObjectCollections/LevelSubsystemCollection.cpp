#include "World/ObjectCollections/LevelSubsystemCollection.h"

void LevelSubsystemCollection::BeginPlay()
{
    InitObject([](LevelSubsystem* subsystem)
        {
            subsystem->Initialize();
        });
}

void LevelSubsystemCollection::Update(float deltaTime)
{
    ForEach([deltaTime](LevelSubsystem* subsystem)
        {
            subsystem->Update(deltaTime);
        });
}

void LevelSubsystemCollection::BeginDestroyObject(LevelSubsystem* subsystem)
{
    subsystem->Deinitialize();
}