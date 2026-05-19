#ifndef __UI_SYSTEM_H_INCLUDED__
#define __UI_SYSTEM_H_INCLUDED__

#include "World/ObjectCollections/WidgetCollection.h"
#include "World/SpatialGraph/SpatialGraph.h"
#include "World/SpawnInfos.h"

class InputManager;
class UserWidget;

/**
 * Central UI runtime system.
 *
 * Responsible for:
 * - widget lifetime management
 * - UI hierarchy updates
 * - UI input forwarding
 * - UI rendering submission
 *
 * The UISystem owns a dedicated SpatialGraph separate from the world scene graph.
 */
class UISystem
{
public:
	~UISystem();

	void OnLevelUnload();

	void FlushPendingAdds();
	void UpdateTransform();
	void UpdateInputs(InputManager* inputManager);
	void Update(float deltaTime);
	void FlushPendingDestroys();

	/**
	 * Returns widget internal raw container.
	 */
	std::vector<Widget*> GetWidgets() { return widgetsCollection.GetCollection(); }
	const std::vector<Widget*> GetWidgets() const { return widgetsCollection.GetCollection(); }

	SpatialGraph* GetUIGraph() { return &graph; }
	const SpatialGraph* GetUIGraph() const { return &graph; }

	template<typename T, typename... Args>
	T* CreateUserWidget(std::string name, const UISpawnInfo& spawnInfo, Args&&... args);

	/**
	* Retrieves first widget by name and type.
	*/
	template<typename T>
	T* GetUserWidget(std::string name);

	template<typename T>
	const T* GetUserWidget(std::string name) const;

	// Temp
	void AddWidget(Widget* widget) { widgetsCollection.RegisterToAdd(widget); }

	/**
	 * Retrieves first widget matching type.
	 */
	template<typename T>
	T* GetUserWidget();

	template<typename T>
	const T* GetUserWidget() const;

	/**
	 * Destruction requests
	 */
	void RegisterToDestroy(Widget* widget);

	/**
	 * Builds the frame render queue from all renderable runtime objects.
	 */
	void BuildRenderQueue(RenderQueue& queue)
	{
		graph.BuildRenderQueue(queue);
	}

private:
	void InternalSpawnUserWidget(UserWidget* userWidget, std::string name, const UISpawnInfo& spawnInfo);

	SpatialGraph graph;
	WidgetCollection widgetsCollection;
};

#include "UISystem.inl"

#endif // __UI_SYSTEM_H_INCLUDED__