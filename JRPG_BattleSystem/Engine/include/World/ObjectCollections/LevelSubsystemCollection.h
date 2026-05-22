#ifndef __LEVEL_SUBSYSTEM_COLLECTION_H_INCLUDED__
#define __LEVEL_SUBSYSTEM_COLLECTION_H_INCLUDED__

#include "ObjectCollection.h"
#include "World/Level/LevelSubsystem.h"

/**
 * Collection specialized for LevelSubsystem.
 * Handles subsystems lifecycle.
 */
class LevelSubsystemCollection : public ObjectCollection<LevelSubsystem>
{
public:
	void BeginPlay();
	void Update(float deltaTime);

private:
	void BeginDestroyObject(LevelSubsystem* subsystem) override;
};

#endif // __LEVEL_SUBSYSTEM_COLLECTION_H_INCLUDED__