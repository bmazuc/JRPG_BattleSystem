#pragma once

#include "RenderQueue.h"

class IRenderable
{
public:
	virtual void AddToRenderQueue(RenderQueue& queue) = 0;
};