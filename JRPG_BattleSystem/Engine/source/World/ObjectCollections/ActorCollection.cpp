#include "World/ObjectCollections/ActorCollection.h"

void ActorCollection::BeginPlay()
{
    InitObject([this](Actor* actor)
        {
            actor->BeginPlay();
            actor->SetupInputs(playerController);
            actor->ComponentsBeginPlay();
        });
}

void ActorCollection::Update(float deltaTime)
{
    ForEach([deltaTime](Actor* actor)
        {
            actor->Update(deltaTime);
            actor->UpdateComponents(deltaTime);
        });
}

void ActorCollection::ProcessComponentsAdd()
{
    ForEach([](Actor* actor)
        {
            actor->ProcessComponentsAdd();
        });
}

void ActorCollection::ProcessComponentsDestroy()
{
    ForEach([](Actor* actor)
        {
            actor->ProcessComponentsDestroy();
        });
}

void ActorCollection::BeginDestroyObject(Actor* actor)
{
    actor->NativeBeginDestroy();
}