#ifndef __OBJECT_COLLECTION_INCLUDED__
#define __OBJECT_COLLECTION_INCLUDED__

#include <vector>
#include <string>

/**
 * Generic container for engine objects with safe lifetime management.
 *
 * Handles:
 * - safe iteration during frame updates
 * - deferred add/removal to avoid invalidation
 * - ownership of runtime objects (manual delete)
 *
 * This class acts as a lightweight runtime object manager.
 */
template<typename T>
class ObjectCollection
{
public:
	/**
	 * Iterates safely over all objects in the collection.
	 * Objects added or removed during iteration are deferred.
	 */
	template<typename Func>
	void ForEach(Func&& func)
	{
		for (T* object : objects)
		{
			if (object)
			{
				func(object);
			}
		}
	}

	/**
	 * Iterates safely over all objects pending for init.
	 */
	template<typename Func>
	void InitObject(Func&& func)
	{
		for (T* object : pendingInitObjects)
		{
			if (object)
			{
				func(object);
			}
		}
		pendingInitObjects.clear();
	}

	/**
	 * Adds an object to the collection.
	 * If iteration is in progress, defers insertion to avoid invalidation.
	 */
	void RegisterToAdd(T* object)
	{
		if (isClearing)
		{
			delete object;
			return;
		}
		pendingAddObjects.push_back(object);
	}

	/**
	 * Marks an object for destruction.
	 * Actual removal happens after iteration ends.
	 */
	void RegisterToDestroy(T* object)
	{
		if (!isClearing)
		{
			pendingDestroyObjects.push_back(object);
		}
	}

	/**
	 * Deletes all objects immediately.
	 * Clears ownership of the collection.
	 */
	void Clear()
	{
		isClearing = true;
		for (T* object : objects)
		{
			BeginDestroyObject(object);
			delete object;
		}
		objects.clear();

		for (T* object : pendingAddObjects)
		{
			BeginDestroyObject(object);
			delete object;
		}
		pendingAddObjects.clear();

		for (T* object : pendingDestroyObjects)
		{
			BeginDestroyObject(object);
			delete object;
		}
		pendingDestroyObjects.clear();

		pendingInitObjects.clear();

		isClearing = false;
	}

	/**
	 * Retrieves first object by name and type.
	 */
	template<typename C>
	const C* Get(std::string name) const 
	{ 
		for (T* object : objects)
		{
			if (object)
			{
				if (object->GetName() == name)
				{
					if (C* casted = dynamic_cast<C*>(object))
					{
						return casted;
					}
				}
			}
		}
		return nullptr;
	}

	template<typename C>
	C* Get(std::string name)
	{ 
		for (T* object : objects)
		{
			if (object)
			{
				if (object->GetName() == name)
				{
					if (C* casted = dynamic_cast<C*>(object))
					{
						return casted;
					}
				}
			}
		}
		return nullptr;
	}

	/**
	 * Retrieves first object matching type.
	 */
	template<typename C>
	C* Get()
	{
		for (T* object : objects)
		{
			if (object)
			{
				if (C* casted = dynamic_cast<C*>(object))
				{
					return casted;
				}
			}
		}
		return nullptr;
	}

	template<typename C>
	const C* Get() const
	{
		for (T* object : objects)
		{
			if (object)
			{
				if (C* casted = dynamic_cast<C*>(object))
				{
					return casted;
				}
			}
		}
		return nullptr;
	}

	/**
	 * Returns internal raw container.
	 */
	const std::vector<T*>& GetCollection() const { return objects; }
	std::vector<T*>& GetCollection() { return objects; }

	/**
	 * RegisterToAdd all pending create objects to objects and clear the list.
	 */
	void FlushPendingAdds()
	{
		std::vector<T*> newObjects = pendingAddObjects;
		pendingAddObjects.clear();

		for (T* object : newObjects)
		{
			if (object)
			{
				objects.push_back(object);
				pendingInitObjects.push_back(object);
			}
		}
	}

	/**
	 * Remove all pending destroy objects from objects and clear the list.
	 */
	void FlushPendingDestroys()
	{
		std::vector<T*> objectsToDestroy = pendingDestroyObjects;
		pendingDestroyObjects.clear();

		for (T* objectToDestroy : objectsToDestroy)
		{
			if (objectToDestroy)
			{
				BeginDestroyObject(objectToDestroy);

				objects.erase(std::remove(objects.begin(), objects.end(), objectToDestroy), objects.end());
				delete objectToDestroy;
			}
		}
	}

protected:
	virtual void BeginDestroyObject(T* object) {}
	virtual void DeleteObject(T* object)
	{
		delete object;
	}

	// Active objects in the collection
	std::vector<T*> objects;

private:
	// Deferred operations
	std::vector<T*> pendingAddObjects;
	std::vector<T*> pendingInitObjects;
	std::vector<T*> pendingDestroyObjects;

	bool isClearing = false;
};

#endif // __SCENE_OBJECT_COLLECTION_INCLUDED__