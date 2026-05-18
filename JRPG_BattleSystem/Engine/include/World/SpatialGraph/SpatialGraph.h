#ifndef __SPATIAL_GRAPH_H_INCLUDED__
#define __SPATIAL_GRAPH_H_INCLUDED__

#include "World/SpatialGraph/SpatialNode.h"
#include "Rendering/RenderQueue.h"

/**
 * Spatial graph responsible for managing all transform nodes.
 * It acts as a central system to update hierarchical transforms (parent / child relationships) for the level.
 */
class SpatialGraph
{
public:
	/**
	 * Updates all node transforms in the graph.
	 */
	void UpdateTransforms();

	void BuildRenderQueue(RenderQueue& queue);

	/**
	 * Registers a node into the level graph.
	 */
	void AddNode(SpatialNode* node);

	/**
	 * Removes a node from the level graph.
	 */
	void RemoveNode(SpatialNode* node);

	/**
	 * Clears all registered nodes.
	 */
	void Clear();

private:
	// All root nodes managed by the graph.
	std::vector<SpatialNode*> nodes;
};

#endif // __SPATIAL_GRAPH_H_INCLUDED__