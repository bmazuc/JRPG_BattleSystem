#ifndef __LEVEL_SUBSYSTEM_H_INCLUDED__
#define __LEVEL_SUBSYSTEM_H_INCLUDED__

#include <string>

class Level;

/**
 * Base class for auto initialized systems that share the lifetime of a level.
 */
class LevelSubsystem
{
public:
	virtual ~LevelSubsystem() = default;
	/**
	 * Called once when the level starts or system is added.
	 */
	virtual void Initialize() {}

	/**
	 * Called once when the level ends.
	 */
	virtual void Deinitialize() {}

	/**
	 * Called once per frame.
	 */
	virtual void Update(float deltaTime) {}

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

	Level* GetScene() { return level; }
	const Level* GetScene() const { return level; }

	void SetScene(Level* newScene) { level = newScene; }

protected:
	// Level owning this actor.
	Level* level;

	// Identifier used for lookup.
	std::string name = "";
};

#endif // __LEVEL_SUBSYSTEM_H_INCLUDED__