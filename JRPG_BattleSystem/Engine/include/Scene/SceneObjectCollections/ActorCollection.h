#ifndef __ACTOR_COLLECTION_INCLUDED__
#define __ACTOR_COLLECTION_INCLUDED__

#include "ObjectCollection.h"
#include "Scene/Actor.h"

class PlayerController;

class ActorCollection : public ObjectCollection<Actor>
{
public:
	void BeginPlay();
	void Update(float deltaTime);

	void SetupInputs(PlayerController* _playerController);

	void SetPlayerController(PlayerController* newPlayerController) { playerController = newPlayerController; }

	void ProcessComponentsAdd();
	void ProcessComponentsDestroy();

private:
	void InitObject(Actor* actor) override;

	void InternalBeginPlay(Actor* actor) override
	{
		ObjectCollection<Actor>::InternalBeginPlay(actor);
		actor->ComponentsBeginPlay();
		actor->SetupInputs(playerController);
	}

	void InternalUpdate(Actor* actor, float deltaTime)
	{
		ObjectCollection<Actor>::InternalUpdate(actor, deltaTime);
		actor->UpdateComponents(deltaTime);
	}

	PlayerController* playerController;
};

#endif // __ACTOR_COLLECTION_INCLUDED__