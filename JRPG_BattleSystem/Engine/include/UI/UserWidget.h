#ifndef __USER_WIDGET_H_INCLUDED__
#define __USER_WIDGET_H_INCLUDED__

#include "Widget.h"
#include "World/SpawnInfos.h"

/**
 * Base class for interactive/custom UI widgets.
 * UserWidget extends Widget with a higher-level lifecycle intended for gameplay/UI logic.
 *
 * Typical usage:
 * - derive from UserWidget
 * - override Construct() for initialization
 * - override Update() for per-frame logic
 * - create child widgets using CreateWidget()
 */
class UserWidget : public Widget
{
public:
	/**
	 * Called once when the level starts or widget is created.
	 */
	virtual void Construct() {}

	/**
	 * Called once per frame.
	 */
	virtual void Update(float deltaTime) {}

	/**
	 * Create a widget and attach it to this user widget if no parent or parent not in this userwidget.
	 */
	template<typename T, typename... Args>
	T* CreateWidget(std::string name, const UISpawnInfo& spawnInfo, Args&&... args);

private:
	void InternalSpawnWidget(Widget* widget, std::string name, const UISpawnInfo& spawnInfo);
};

#include "UserWidget.inl"

#endif // __USER_WIDGET_H_INCLUDED__