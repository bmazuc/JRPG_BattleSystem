#include "Scene/SceneGraph/SceneGraph.h"

void SceneGraph::UpdateTransforms()
{
	for (SceneNode* node : nodes)
	{
		if (node)
		{
			if (!node->HasParent())
			{
				node->UpdateTransform();
			}
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