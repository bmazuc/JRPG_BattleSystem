#include "World/SceneGraph/SpatialGraph.h"

void SpatialGraph::UpdateTransforms()
{
	for (SpatialNode* node : nodes)
	{
		if (node)
		{
			node->UpdateTransform();
		}
	}
}

void SpatialGraph::BuildRenderQueue(RenderQueue& queue)
{
	for (SpatialNode* node : nodes)
	{
		if (node)
		{
			node->BuildRenderQueue(queue);
		}
	}
}

void SpatialGraph::AddNode(SpatialNode* node)
{
	nodes.push_back(node);
}

void SpatialGraph::RemoveNode(SpatialNode* node)
{
	nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}

void SpatialGraph::Clear()
{
	nodes.clear();
}