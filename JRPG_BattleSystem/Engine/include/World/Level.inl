template<typename T, typename... Args>
T* Level::SpawnActor(std::string name, const ActorSpawnInfo& spawnInfo, Args&&... args)
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	T* actor = new T(std::forward<Args>(args)...);
	InternalSpawnActor(actor, name, spawnInfo);
	return actor;
}

template<typename T>
T* Level::GetActor(std::string name)
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>(name);
}

template<typename T>
const T* Level::GetActor(std::string name) const
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>(name);
}

template<typename T>
T* Level::GetActor()
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>();
}

template<typename T>
const T* Level::GetActor() const
{
	static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
	return actorsCollection.Get<T>();
}

template<typename T, typename... Args>
T* Level::AddSubsystem(std::string name, Args&&... args)
{
	static_assert(std::is_base_of<LevelSubsystem, T>::value, "T must inherit LevelSubsystem");
	T* subsystem = new T(std::forward<Args>(args)...);
	subsystem->SetName(name);
	sceneSubsystemCollection.RegisterToAdd(subsystem);
	return subsystem;
}

/**
 * Retrieves first subsystem by name and type.
 */
template<typename T>
T* Level::GetSubsystem(std::string name)
{
	static_assert(std::is_base_of<LevelSubsystem, T>::value, "T must inherit LevelSubsystem");
	return sceneSubsystemCollection.Get<T>(name);
}

template<typename T>
const T* Level::GetSubsystem(std::string name) const
{
	static_assert(std::is_base_of<LevelSubsystem, T>::value, "T must inherit LevelSubsystem");
	return sceneSubsystemCollection.Get<T>(name);
}

/**
 * Retrieves first subsystem matching type.
 */
template<typename T>
T* Level::GetSubsystem() 
{
	static_assert(std::is_base_of<LevelSubsystem, T>::value, "T must inherit LevelSubsystem");
	return sceneSubsystemCollection.Get<T>();
}

template<typename T>
const T* Level::GetSubsystem() const
{
	static_assert(std::is_base_of<LevelSubsystem, T>::value, "T must inherit LevelSubsystem");
	return sceneSubsystemCollection.Get<T>();
}