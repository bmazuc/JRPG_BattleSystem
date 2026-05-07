#pragma once

#include "SceneObjectCollection.h"
#include "Scene/Actor.h"

class PlayerController;

class ActorCollection : public SceneObjectCollection<Actor>
{
public:
	void SetPlayerController(PlayerController* newPlayerController) { playerController = newPlayerController; }

private:
	void InternalBeginPlay(Actor* actor) override
	{
		SceneObjectCollection<Actor>::InternalBeginPlay(actor);
		actor->ComponentsBeginPlay();
		actor->SetupInputs(playerController);
	}

	void InternalUpdate(Actor* actor, float deltaTime)
	{
		SceneObjectCollection<Actor>::InternalUpdate(actor, deltaTime);
		actor->UpdateComponents(deltaTime);
	}

	PlayerController* playerController;
};