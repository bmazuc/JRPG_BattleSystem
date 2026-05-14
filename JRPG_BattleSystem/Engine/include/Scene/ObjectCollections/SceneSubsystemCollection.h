#pragma once

#include "ObjectCollection.h"
#include "Scene/SceneSubsystem.h"

/**
 * Collection specialized for SceneSubsystem.
 * Handles subsystems lifecycle.
 */
class SceneSubsystemCollection : public ObjectCollection<SceneSubsystem>
{
public:
	void BeginPlay();
	void Update(float deltaTime);

private:
	void InitObject(SceneSubsystem* subsystem) override;
	void BeginDestroyObject(SceneSubsystem* subsystem) override;
};