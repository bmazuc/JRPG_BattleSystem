#include "World/Level/Scene/Scene.h"
#include "Components/Camera/CameraComponent.h"

void Scene::Unload()
{
	graph.Clear();
	actorsCollection.Clear();
}

void Scene::BeginPlay()
{
	actorsCollection.BeginPlay();
}

void Scene::SetPlayerController(PlayerController* playerController)
{
	actorsCollection.SetPlayerController(playerController);
}

void Scene::FlushPendingAdds()
{
	actorsCollection.FlushPendingAdds();
	actorsCollection.ProcessComponentsAdd();
}

void Scene::SyncGraph()
{
	for (Actor* actor : dirtyActors)
	{
		actor->GetRoot()->GetNode()->SyncGraph(&graph);
	}
	dirtyActors.clear();
}

void Scene::UpdateTransform()
{
	graph.UpdateTransforms();
}

void Scene::Update(float deltaTime)
{
	actorsCollection.Update(deltaTime);
}

void Scene::FlushPendingDestroys()
{
	actorsCollection.FlushPendingDestroys();
	actorsCollection.ProcessComponentsDestroy();
}

void Scene::RegisterToDestroy(Actor* actor)
{
	actorsCollection.RegisterToDestroy(actor);
}

void Scene::InternalSpawnActor(Actor* actor, std::string name, const ActorSpawnInfo& spawnInfo)
{
	actor->SetName(name);
	actor->SetScene(this);
	actor->AttachToActor(spawnInfo.parent);

	if (spawnInfo.transformSpace == TransformSpace::World)
	{
		actor->SetWorldPosition(spawnInfo.location);
		actor->SetWorldRotate(spawnInfo.rotate);
		actor->SetWorldScale(spawnInfo.scale);
	}
	else
	{
		actor->SetLocalPosition(spawnInfo.location);
		actor->SetLocalRotate(spawnInfo.rotate);
		actor->SetLocalScale(spawnInfo.scale);
	}

	actorsCollection.RegisterToAdd(actor);
	RegisterDirtyActor(actor);
}

glm::vec2 Scene::ScreenToWorld(glm::vec2 screenPos)
{
	glm::vec2 worldPos = screenPos;

	if (activeCamera)
	{
		worldPos -= activeCamera->GetWorldPosition();
		worldPos /= activeCamera->GetZoom();
	}

	return worldPos;
}