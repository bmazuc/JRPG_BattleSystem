#ifndef __TEST_SCENE_SUBSYSTEM_H_INCLUDED__
#define __TEST_SCENE_SUBSYSTEM_H_INCLUDED__

#include "Scene/SceneSubsystem.h"

class TestSceneSubsystem : public SceneSubsystem
{
public:
	void Initialize() override;
	void Deinitialize() override;
};

#endif // __TEST_SCENE_SUBSYSTEM_H_INCLUDED__