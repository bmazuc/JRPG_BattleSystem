#include "World/SpatialGraph/SpatialGraph.h"
#include "World/SpatialGraph/SpatialNode.h"

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

void SpatialGraph::BuildRenderQueue(RenderQueue& queue, ISpatialNodeOrderProvider* provider)
{
	for (SpatialNode* node : nodes)
	{
		if (node)
		{
			node->BuildRenderQueue(queue, provider);
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