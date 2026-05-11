#ifndef __SCENE_GRAPH_H_INCLUDED__
#define __SCENE_GRAPH_H_INCLUDED__

#include "Scene/SceneGraph/SceneNode.h"

class SceneGraph
{
public:
	// Update nodes transforms
	void UpdateTransforms();

	void AddNode(SceneNode* node);
	void RemoveNode(SceneNode* node);
	void Clear();

private:
	std::vector<SceneNode*> nodes;
};

#endif // __SCENE_GRAPH_H_INCLUDED__