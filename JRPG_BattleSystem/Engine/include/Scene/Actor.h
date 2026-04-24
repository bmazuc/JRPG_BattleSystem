#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include <glm/vec2.hpp>
#include <vector>

class Component;

class Actor
{
public:
	Actor();
	~Actor();

	virtual void Init() {}
	virtual void Update(float deltaTime) {}

	void AttachToActor(Actor* actor);
	void Detach();

	void UpdateTransforms();
	void UpdateComponents(float deltaTime);

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");

		T* comp = new T(std::forward<Args>(args)...);
		comp->SetOwner(this);
		comp->SetParent(root);

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

	glm::vec2 GetWorldPosition() const;
	float GetWorldRotate() const;
	glm::vec2 GetWorldScale() const;

	void SetWorldPosition(glm::vec2 position);
	void SetWorldRotate(float rotate);
	void SetWorldScale(glm::vec2 scale);

	glm::vec2 GetLocalPosition() const;
	float GetLocalRotate() const;
	glm::vec2 GetLocalScale() const;

	void SetLocalPosition(glm::vec2 position);
	void SetLocalRotate(float rotate);
	void SetLocalScale(glm::vec2 scale);

	Component* GetRoot() const { return root; }

private:
	Component* root;
	std::vector<Component*> components;
};

#endif // __ACTOR_H_INCLUDED__