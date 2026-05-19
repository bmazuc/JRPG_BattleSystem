#ifndef __RENDERABLE_H_INCLUDED__
#define __RENDERABLE_H_INCLUDED__

#include "RenderQueue.h"

/**
 * Interface implemented by objects that can submit render data.
 * Renderable objects do not render themselves directly. Instead, they generate render items and push them into a RenderQueue, 
 * allowing centralized rendering, sorting, and batching.
 */
class IRenderable
{
public:
	virtual void AddToRenderQueue(RenderQueue& queue) = 0;
};

#endif // __RENDERABLE_H_INCLUDED__