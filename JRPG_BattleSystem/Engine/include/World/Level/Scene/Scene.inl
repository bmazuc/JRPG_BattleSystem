template<typename T, typename... Args>
T* Scene::SpawnActor(std::string name, const ActorSpawnInfo& spawnInfo, Args&&... args)
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	T* actor = new T(std::forward<Args>(args)...);
	InternalSpawnActor(actor, name, spawnInfo);
	return actor;
}

template<typename T>
T* Scene::GetActor(std::string name)
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>(name);
}

template<typename T>
const T* Scene::GetActor(std::string name) const
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>(name);
}

template<typename T>
T* Scene::GetActor()
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>();
}

template<typename T>
const T* Scene::GetActor() const
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>();
}