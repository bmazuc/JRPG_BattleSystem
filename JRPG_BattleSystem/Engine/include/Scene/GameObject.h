#ifndef __GAME_OBJECT_H_INCLUDED__
#define __GAME_OBJECT_H_INCLUDED__

#include <vector>

class Component;

class GameObject
{
public:
	~GameObject();

	virtual void Init() {}
	virtual void Update() {}

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");

		T* comp = new T(std::forward<Args>(args)...);
		comp->SetOwner(this);

		components.emplace_back(comp);

		return comp;
	}

	template<typename T>
	T* GetComponent() 
	{
		for (auto& c : components) {
			T* casted = dynamic_cast<T*>(c);

			if (casted)
				return casted;
		}
		return nullptr;
	}

private:
	std::vector<Component*> components;
};

#endif // __GAME_OBJECT_H_INCLUDED__