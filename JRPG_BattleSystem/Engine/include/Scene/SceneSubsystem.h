#ifndef __SCENE_SUBSYSTEM_H_INCLUDED__
#define __SCENE_SUBSYSTEM_H_INCLUDED__

#include <string>

class Scene;

/**
 * Base class for auto initialized systems that share the lifetime of a scene.
 */
class SceneSubsystem
{
public:
	virtual ~SceneSubsystem() = default;
	/**
	 * Called once when the scene starts or system is added.
	 */
	virtual void Initialize() {}

	/**
	 * Called once when the scene ends.
	 */
	virtual void Deinitialize() {}

	/**
	 * Called once per frame.
	 */
	virtual void Update(float deltaTime) {}

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }

	void SetScene(Scene* newScene) { scene = newScene; }

protected:
	// Scene owning this actor.
	Scene* scene;

	// Identifier used for lookup.
	std::string name = "";
};

#endif // __SCENE_SUBSYSTEM_H_INCLUDED__