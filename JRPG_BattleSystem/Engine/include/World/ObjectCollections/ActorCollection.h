#ifndef __ACTOR_COLLECTION_INCLUDED__
#define __ACTOR_COLLECTION_INCLUDED__

#include "ObjectCollection.h"
#include "World/Level/Scene/Actor.h"

class PlayerController;

/**
 * Specialized collection for Actor objects.
 *
 * Extends ObjectCollection with:
 * - lifecycle integration (BeginPlay / Update)
 * - component processing
 * - player controller injection
 */
class ActorCollection : public ObjectCollection<Actor>
{
public:
	void BeginPlay();
	void Update(float deltaTime);

	/**
	 * Injects player controller into actors that need input.
	 */
	void SetupInputs(PlayerController* _playerController);

	void SetPlayerController(PlayerController* newPlayerController) { playerController = newPlayerController; }

	void ProcessComponentsAdd();
	void ProcessComponentsDestroy();

private:
	void InitObject(Actor* actor) override;
	void BeginDestroyObject(Actor* actor) override;
	PlayerController* playerController;
};

#endif // __ACTOR_COLLECTION_INCLUDED__