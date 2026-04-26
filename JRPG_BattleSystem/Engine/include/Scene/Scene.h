#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

class CameraComponent;

#include "Actor.h"

class Scene
{
public:
	~Scene();

	void Init();

	void UpdateTransforms();
	void Update(float deltaTime);
	void ProcessDestroy();

	CameraComponent* GetActiveCamera() { return activeCamera; }
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	std::vector<Actor*> GetActors() const { return actors; }

	template<typename T, typename... Args>
	T* CreateActors(Args&&... args)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");

		T* actor = new T(std::forward<Args>(args)...);
		actor->SetScene(this);
		actors.push_back(actor);

		return actor;
	}

	void RegisterToDestroy(Actor* actor);

private:
	std::vector<Actor*> actors;
	std::vector<Actor*> actorsToDestroy;
	CameraComponent* activeCamera;
};

#endif // __SCENE_H_INCLUDED__