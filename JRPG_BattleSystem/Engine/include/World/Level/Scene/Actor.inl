template<typename T, typename... Args>
T* Actor::CreateComponent(std::string name, Args&&... args)
{
	static_assert(std::is_base_of<ActorComponent, T>::value, "T must inherit ActorComponent");
	T* component = new T(std::forward<Args>(args)...);
	RegisterComponent(component, name);
	return component;
}

template<typename T, typename... Args>
T* Actor::SpawnSceneComponent(std::string name, const SceneComponentSpawnInfo& spawnInfo, Args&&... args)
{
	static_assert(std::is_base_of<SceneComponent, T>::value, "T must inherit SceneComponent");
	T* component = new T(std::forward<Args>(args)...);
	RegisterComponent(component, name);
	InternalSpawnSceneComponent(component, spawnInfo);
	return component;
}

template<typename T>
T* Actor::GetComponent(std::string name)
{
	static_assert(std::is_base_of<ActorComponent, T>::value, "T must inherit ActorComponent");
	return componentsCollection.Get<T>(name);
}

template<typename T>
const T* Actor::GetComponent(std::string name) const
{
	static_assert(std::is_base_of<ActorComponent, T>::value, "T must inherit ActorComponent");
	return componentsCollection.Get<T>(name);
}

template<typename T>
T* Actor::GetComponent()
{
	static_assert(std::is_base_of<ActorComponent, T>::value, "T must inherit ActorComponent");
	return componentsCollection.Get<T>();
}

template<typename T>
const T* Actor::GetComponent() const
{
	static_assert(std::is_base_of<ActorComponent, T>::value, "T must inherit ActorComponent");
	return componentsCollection.Get<T>();
}