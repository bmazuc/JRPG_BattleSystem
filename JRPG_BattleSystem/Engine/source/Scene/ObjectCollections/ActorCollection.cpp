#include "Scene/ObjectCollections/ActorCollection.h"

void ActorCollection::BeginPlay()
{
    Iterate([](Actor* actor)
        {
            actor->BeginPlay();
            actor->ComponentsBeginPlay();
        });
}

void ActorCollection::Update(float deltaTime)
{
    Iterate([deltaTime](Actor* actor)
        {
            actor->Update(deltaTime);
            actor->UpdateComponents(deltaTime);
        });
}

void ActorCollection::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    Iterate([_playerController](Actor* actor)
        {
            actor->SetupInputs(_playerController);
        });
}

void ActorCollection::ProcessComponentsAdd()
{
    Iterate([](Actor* actor)
        {
            actor->ProcessComponentsAdd();
        });
}

void ActorCollection::ProcessComponentsDestroy()
{
    Iterate([](Actor* actor)
        {
            actor->ProcessComponentsDestroy();
        });
}

void ActorCollection::InitObject(Actor* actor)
{
    actor->BeginPlay();
    actor->SetupInputs(playerController);
}

void ActorCollection::BeginDestroyObject(Actor* actor)
{
    actor->BeginDestroy();
}