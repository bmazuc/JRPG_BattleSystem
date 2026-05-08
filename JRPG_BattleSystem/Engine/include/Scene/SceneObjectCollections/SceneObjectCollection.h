#ifndef __SCENE_OBJECT_COLLECTION_INCLUDED__
#define __SCENE_OBJECT_COLLECTION_INCLUDED__

#include <vector>
#include <string>

template<typename T>
class SceneObjectCollection
{
public:
	virtual void BeginPlay()
	{
		isIterating = true;
		for (T* object : sceneObjects)
		{
			if (object)
			{
				InternalBeginPlay(object);
			}
		}

		ProcessCreate();
		isIterating = false;
	}

	virtual void Update(float deltaTime)
	{
		isIterating = true;
		for (T* object : sceneObjects)
		{
			if (object)
			{
				InternalUpdate(object, deltaTime);
			}
		}

		ProcessCreate();
		isIterating = false;
	}

	void UpdateTransforms()
	{
		for (T* object : sceneObjects)
		{
			if (object)
			{
				if (!object->GetRoot()->HasParent())
				{
					object->UpdateTransforms();
				}
			}
		}
	}

	void Add(T* object)
	{
		if (isIterating)
		{
			pendingCreateSceneObjects.push_back(object);
		}
		else
		{
			sceneObjects.push_back(object);
		}
	}

	void Clear()
	{
		for (T* object : sceneObjects)
		{
			delete object;
		}

		sceneObjects.clear();
	}

	void RegisterToDestroy(T* object)
	{
		pendingDestroySceneObjects.push_back(object);
	}

	void ProcessDestroy()
	{
		for (T* objectToDestroy : pendingDestroySceneObjects)
		{
			if (objectToDestroy)
			{
				objectToDestroy->DetachFromHierarchy();

				sceneObjects.erase(std::remove(sceneObjects.begin(), sceneObjects.end(), objectToDestroy), sceneObjects.end());
				delete objectToDestroy;
			}
		}

		pendingDestroySceneObjects.clear();
	}

	template<typename C>
	const C* Get(std::string name) const 
	{ 
		for (T* object : sceneObjects)
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
		for (T* object : sceneObjects)
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
		for (T* object : sceneObjects)
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
		for (T* object : sceneObjects)
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

	const std::vector<T*> GetCollection() const { return sceneObjects; }
	std::vector<T*> GetCollection() { return sceneObjects; }

protected:
	virtual void InternalBeginPlay(T* object)
	{
		object->BeginPlay();
	}

	virtual void InternalUpdate(T* object, float deltaTime)
	{
		object->Update(deltaTime);
	}

	// All scene objects living in the scene
	std::vector<T*> sceneObjects;
	// All scene objects waiting to be created
	std::vector<T*> pendingCreateSceneObjects;
	// All scene objects marked for destruction
	std::vector<T*> pendingDestroySceneObjects;

private:
	void ProcessCreate()
	{
		while (pendingCreateSceneObjects.size() > 0)
		{
			std::vector<T*> newObjects = pendingCreateSceneObjects;
			pendingCreateSceneObjects.clear();

			for (T* object : newObjects)
			{
				if (object)
				{
					InternalBeginPlay(object);
					sceneObjects.push_back(object);
				}
			}
		}
	}

	bool isIterating = false;
};

#endif // __SCENE_OBJECT_COLLECTION_INCLUDED__