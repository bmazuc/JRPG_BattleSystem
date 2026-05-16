#ifndef __SCENE_GRAPH_H_INCLUDED__
#define __SCENE_GRAPH_H_INCLUDED__

#include "Scene/SceneGraph/SceneNode.h"
#include "Rendering/RenderQueue.h"

/**
 * Scene graph responsible for managing all transform nodes.
 * It acts as a central system to update hierarchical transforms (parent / child relationships) for the scene.
 */
class SceneGraph
{
public:
	/**
	 * Updates all node transforms in the graph.
	 */
	void UpdateTransforms();

	void BuildRenderQueue(RenderQueue& queue);

	/**
	 * Registers a node into the scene graph.
	 */
	void AddNode(SceneNode* node);

	/**
	 * Removes a node from the scene graph.
	 */
	void RemoveNode(SceneNode* node);

	/**
	 * Clears all registered nodes.
	 */
	void Clear();

private:
	// All root nodes managed by the graph.
	std::vector<SceneNode*> nodes;
};

#endif // __SCENE_GRAPH_H_INCLUDED__