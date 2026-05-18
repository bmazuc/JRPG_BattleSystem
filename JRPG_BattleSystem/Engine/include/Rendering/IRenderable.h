#ifndef __RENDERABLE_H_INCLUDED__
#define __RENDERABLE_H_INCLUDED__

#include "RenderQueue.h"

class IRenderable
{
public:
	virtual void AddToRenderQueue(RenderQueue& queue) = 0;
};

#endif // __RENDERABLE_H_INCLUDED__