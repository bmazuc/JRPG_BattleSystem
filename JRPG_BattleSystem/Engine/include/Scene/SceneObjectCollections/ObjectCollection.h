#ifndef __OBJECT_COLLECTION_INCLUDED__
#define __OBJECT_COLLECTION_INCLUDED__

#include <vector>
#include <string>

template<typename T>
class ObjectCollection
{
public:
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

	void Add(T* object)
	{
		if (isIterating)
		{
			pendingAddObjects.push_back(object);
		}
		else
		{
			objects.push_back(object);
		}
	}

	void Clear()
	{
		for (T* object : objects)
		{
			delete object;
		}

		objects.clear();
	}

	void RegisterToDestroy(T* object)
	{
		pendingDestroyObjects.push_back(object);
	}

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

	void ProcessDestroy()
	{
		for (T* objectToDestroy : pendingDestroyObjects)
		{
			if (objectToDestroy)
			{
				objectToDestroy->DetachFromHierarchy();

				objects.erase(std::remove(objects.begin(), objects.end(), objectToDestroy), objects.end());
				delete objectToDestroy;
			}
		}

		pendingDestroyObjects.clear();
	}

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

	const std::vector<T*>& GetCollection() const { return objects; }
	std::vector<T*>& GetCollection() { return objects; }

protected:
	virtual void InitObject(T* object) {}

	virtual void InternalBeginPlay(T* object)
	{
		object->BeginPlay();
	}

	virtual void InternalUpdate(T* object, float deltaTime)
	{
		object->Update(deltaTime);
	}

	// All objects contains in this collection
	std::vector<T*> objects;
	// All objects waiting to be add
	std::vector<T*> pendingAddObjects;
	// All objects marked for destruction
	std::vector<T*> pendingDestroyObjects;

private:
	bool isIterating = false;
};

#endif // __SCENE_OBJECT_COLLECTION_INCLUDED__