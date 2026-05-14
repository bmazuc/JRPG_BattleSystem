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

template<typename T, typename... Args>
T* Scene::CreateUIElement(std::string name, const UISpawnInfo& spawnInfo, Args&&... args)
{
	static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
	T* element = new T(std::forward<Args>(args)...);
	InternalSpawnUIElement(element, name, spawnInfo);
	return element;
}

template<typename T>
T* Scene::GetUIElement(std::string name)
{
	static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
	return uiElementsCollection.Get<T>(name);
}

template<typename T>
const T* Scene::GetUIElement(std::string name) const
{
	static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
	return uiElementsCollection.Get<T>(name);
}

template<typename T>
T* Scene::GetUIElement()
{
	static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
	return uiElementsCollection.Get<T>();
}

template<typename T>
const T* Scene::GetUIElement() const
{
	static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
	return uiElementsCollection.Get<T>();
}

template<typename T, typename... Args>
T* Scene::AddSubsystem(std::string name, Args&&... args)
{
	static_assert(std::is_base_of<SceneSubsystem, T>::value, "T must inherit SceneSubsystem");
	T* subsystem = new T(std::forward<Args>(args)...);
	subsystem->SetName(name);
	sceneSubsystemCollection.Add(subsystem);
	return subsystem;
}

/**
 * Retrieves first subsystem by name and type.
 */
template<typename T>
T* Scene::GetSubsystem(std::string name)
{
	static_assert(std::is_base_of<SceneSubsystem, T>::value, "T must inherit SceneSubsystem");
	return sceneSubsystemCollection.Get<T>(name);
}

template<typename T>
const T* Scene::GetSubsystem(std::string name) const
{
	static_assert(std::is_base_of<SceneSubsystem, T>::value, "T must inherit SceneSubsystem");
	return sceneSubsystemCollection.Get<T>(name);
}

/**
 * Retrieves first subsystem matching type.
 */
template<typename T>
T* Scene::GetSubsystem() 
{
	static_assert(std::is_base_of<SceneSubsystem, T>::value, "T must inherit SceneSubsystem");
	return sceneSubsystemCollection.Get<T>();
}

template<typename T>
const T* Scene::GetSubsystem() const
{
	static_assert(std::is_base_of<SceneSubsystem, T>::value, "T must inherit SceneSubsystem");
	return sceneSubsystemCollection.Get<T>();
}