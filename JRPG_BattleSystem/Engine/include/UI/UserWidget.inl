template<typename T, typename... Args>
T* UserWidget::CreateWidget(std::string name, const UISpawnInfo& spawnInfo, Args&&... args)
{
	static_assert(std::is_base_of<Widget, T>::value, "T must inherit Widget");

	T* widget = new T(std::forward<Args>(args)...);
	InternalSpawnWidget(widget, name, spawnInfo);
	return widget;
}