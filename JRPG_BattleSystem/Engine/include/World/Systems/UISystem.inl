template<typename T, typename... Args>
T* UISystem::CreateUserWidget(std::string name, const UISpawnInfo& spawnInfo, Args&&... args)
{
	static_assert(std::is_base_of<UserWidget, T>::value, "T must inherit UserWidget");
	T* element = new T(std::forward<Args>(args)...);
	InternalSpawnUserWidget(element, name, spawnInfo);
	return element;
}

template<typename T>
T* UISystem::GetUserWidget(std::string name)
{
	static_assert(std::is_base_of<UserWidget, T>::value, "T must inherit UserWidget");
	return widgetsCollection.Get<T>(name);
}

template<typename T>
const T* UISystem::GetUserWidget(std::string name) const
{
	static_assert(std::is_base_of<UserWidget, T>::value, "T must inherit UserWidget");
	return widgetsCollection.Get<T>(name);
}

template<typename T>
T* UISystem::GetUserWidget()
{
	static_assert(std::is_base_of<UserWidget, T>::value, "T must inherit UserWidget");
	return widgetsCollection.Get<T>();
}

template<typename T>
const T* UISystem::GetUserWidget() const
{
	static_assert(std::is_base_of<UserWidget, T>::value, "T must inherit UserWidget");
	return widgetsCollection.Get<T>();
}