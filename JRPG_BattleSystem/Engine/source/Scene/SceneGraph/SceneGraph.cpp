#include "Scene/SceneGraph/SceneGraph.h"

void SceneGraph::UpdateTransforms()
{
	for (SceneNode* node : nodes)
	{
		if (node)
		{
			node->UpdateTransform();
		}
	}
}

void SceneGraph::BuildRenderQueue(RenderQueue& queue)
{
	for (SceneNode* node : nodes)
	{
		if (node)
		{
			node->BuildRenderQueue(queue);
		}
	}
}

void SceneGraph::AddNode(SceneNode* node)
{
	nodes.push_back(node);
}

void SceneGraph::RemoveNode(SceneNode* node)
{
	nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}

void SceneGraph::Clear()
{
	nodes.clear();
}