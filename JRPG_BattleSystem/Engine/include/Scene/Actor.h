#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include <glm/vec2.hpp>
#include <vector>

class Component;
class Scene;
class PlayerController;

/*
 *	Base class for anything that has a position, rotation, and scale in the game world
 */
class Actor
{
public:
	Actor();
	~Actor();

	/*
	 *	Behavior called after scene loading
	 */
	virtual void Init() {}
	/*
	 *	Behavior called each frame
	 */
	virtual void UpdateInputs(float deltaTime) {}
	/*
	 *	Mark an actor for destroy
	 *	Future upgrade : Add a destroy with a timer
	 */ 
	void Destroy(bool destroyChildren = false);

	/*
	 *	Call after scene loading. Allow to link inputs and behaviour for this actor.
	 */
	virtual void SetupInputs(PlayerController* playerController) {}

	/*
	 *	Attach this actor root to another actor root.
	 *	@param actor the parent actor
	 */
	void AttachToActor(Actor* actor);
	/*
	 *	Detach this actor root from its parent.
	 */
	void Detach();

	/*
	 *	Update components transform.
	 */
	void UpdateTransforms();
	/*
	 *	Called each components init behavior. Called after scene loading.
	 */
	void InitComponents();
	/*
	 *	Called each components update behavior. Called each frame.
	 */
	void UpdateComponents(float deltaTime);
	/*
	 *	Destroy each components marked for destruction.
	 */
	void ProcessComponentsDestroy();

	/*
	 *	Create and add a component to this actor.
	 *	New component parent will be actor root.
	 */
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

	/*
	 *	Get the first component of specified type.
	 */
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
	
	/*
	 *	Get the first component of specified type.
	 */
	template<typename T>
	const T* GetComponent() const
	{
		for (auto& c : components) {
			T* casted = dynamic_cast<T*>(c);

			if (casted)
				return casted;
		}
		return nullptr;
	}

	/*
	 *	Call by component destroy. Register this component inside a list of components to destroy.
	 *	@param component the component to register
	 */
	void RegisterComponentsToDestroy(Component* component);

	Component* GetRoot() { return root; }
	const Component* GetRoot() const{ return root; }

	Actor* GetParent();
	const Actor* GetParent() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }

	void SetScene(Scene* _scene) { scene = _scene; }

	/*
	 *	Transform getter/setter
	 */

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

protected:
	// reference to the scene the actor lives in
	Scene* scene;

private:
	Component* root;
	std::vector<Component*> components;
	std::vector<Component*> componentsToDestroy;

	// Are actor mark for destruction ?
	bool isPendingDestroy = false;
};

#endif // __ACTOR_H_INCLUDED__