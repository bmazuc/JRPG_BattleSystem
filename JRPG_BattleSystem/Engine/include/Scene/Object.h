#ifndef __OBJECT_H_INCLUDED__
#define __OBJECT_H_INCLUDED__

#include <string>

/**
 * Base class for all runtime objects managed by the engine.
 *
 * Object provides common engine-level functionality shared across gameplay, UI, and future engine systems such as:
 * - object identification via name
 * - deferred destruction support
 * - destruction lifecycle hook
 *
 * Objects are not destroyed immediately when marked for deletion.
 * Instead, engine collections process destruction safely at the end of an update cycle to avoid invalid references during iteration.
 */
class Object
{
public:
	/**
	 * Called before object destruction.
	 */
	virtual void BeginDestroy() {}

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

protected:
	// Are object mark for destruction ?
	bool isPendingDestroy = false;

	// Identifier used for lookup.
	std::string name = "";
};

#endif // __OBJECT_H_INCLUDED__