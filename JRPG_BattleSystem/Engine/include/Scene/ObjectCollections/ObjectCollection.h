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
	void Iterate(Func&& func)
	{
		isIterating = true;
		for (T* object : objects)
		{
			if (object)
			{
				func(object);
			}
		}
		isIterating = false;
	}

	/**
	 * Adds an object to the collection.
	 * If iteration is in progress, defers insertion to avoid invalidation.
	 */
	void Add(T* object, bool isRuntime)
	{
		if (isIterating || isRuntime)
		{
			pendingAddObjects.push_back(object);
		}
		else
		{
			objects.push_back(object);
		}
	}

	/**
	 * Deletes all objects immediately.
	 * Clears ownership of the collection.
	 */
	void Clear()
	{
		for (T* object : objects)
		{
			BeginDestroyObject(object);
			delete object;
		}

		objects.clear();
	}

	/**
	 * Marks an object for destruction.
	 * Actual removal happens after iteration ends.
	 */
	void RegisterToDestroy(T* object)
	{
		pendingDestroyObjects.push_back(object);
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
	 * Processes pending additions after iteration.
	 */
	void ProcessAdd()
	{
		while (pendingAddObjects.size() > 0)
		{
			std::vector<T*> newObjects = pendingAddObjects;
			pendingAddObjects.clear();

			for (T* object : newObjects)
			{
				if (object)
				{
					InitObject(object);
					objects.push_back(object);
				}
			}
		}
	}

	/**
	 * Processes pending removals and deletes objects.
	 */
	void ProcessDestroy()
	{
		for (T* objectToDestroy : pendingDestroyObjects)
		{
			if (objectToDestroy)
			{
				BeginDestroyObject(objectToDestroy);

				objects.erase(std::remove(objects.begin(), objects.end(), objectToDestroy), objects.end());
				delete objectToDestroy;
			}
		}

		pendingDestroyObjects.clear();
	}

protected:
	virtual void InitObject(T* object) {}

	virtual void BeginDestroyObject(T* object) {}

	// Active objects in the collection
	std::vector<T*> objects;

private:
	// Deferred operations
	std::vector<T*> pendingAddObjects;
	std::vector<T*> pendingDestroyObjects;

	bool isIterating = false;
};

#endif // __SCENE_OBJECT_COLLECTION_INCLUDED__