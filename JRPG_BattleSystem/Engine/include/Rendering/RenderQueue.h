#ifndef __RENDER_QUEUE_H_INCLUDED__
#define __RENDER_QUEUE_H_INCLUDED__

#include "Rendering/Color.h"

#include <map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>

class Material;
class Font;
enum class TextScaleMode;

/**
 * Base render item stored inside the render queue.
 */
struct RenderItem
{
public:
	RenderItem(glm::mat4 _world) 
		: world(_world) {}

	virtual ~RenderItem() = default;

	glm::mat4 world;
	
};

/**
 * Render item representing a textured quad.
 */
struct RenderTextureItem : public RenderItem
{
public:
	RenderTextureItem(glm::mat4 _world, glm::vec2 _size, Material* _material) 
		: RenderItem(_world), size(_size), material(_material) {}

	glm::vec2 size;
	Material* material;
};

/**
 * Render item representing a text element.
 */
struct RenderTextItem : public RenderItem
{
public:
	RenderTextItem(glm::mat4 _world, float _size, std::string _content, Font* _font, Color _color, TextScaleMode _scaleMode, bool _isCenterX)
		: RenderItem(_world), size(_size), content(_content), font(_font), color(_color), scaleMode(_scaleMode), isCenterX(_isCenterX) {}

	Font* font;
	Color color;

	TextScaleMode scaleMode;
	std::string content;

	float size;
	bool isCenterX;
};

using RenderBucket = std::map<int, std::vector<RenderItem*>>;

/**
 * Frame-local render item container.
 * Renderable objects submit transient render items into this queue every frame.
 * The renderer later consumes and clears the queue.
 * World items are grouped by z-order to preserve rendering order.
 */
struct RenderQueue
{
public:
	void AddWorldItem(RenderItem* item, int zOrder)
	{
		worldBuckets[zOrder].push_back(item);
	}

	void AddUIItem(RenderItem* item)
	{
		uiItems.push_back(item);
	}

	void Clear()
	{
		for (auto it = worldBuckets.begin(); it != worldBuckets.end(); ++it)
		{
			std::vector<RenderItem*>& items = it->second;
			for (RenderItem* item : items)
			{
				delete item;
				item = nullptr;
			}
		}

		for (RenderItem* item : uiItems)
		{
			delete item;
			item = nullptr;
		}
	}

	// Render buckets grouped by z-order.
	RenderBucket worldBuckets;

	std::vector<RenderItem*> uiItems;
};

#endif // __RENDER_QUEUE_H_INCLUDED__