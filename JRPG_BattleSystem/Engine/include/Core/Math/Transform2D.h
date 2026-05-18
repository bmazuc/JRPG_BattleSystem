#ifndef __TRANSFORM_2D_H_INCLUDED__
#define __TRANSFORM_2D_H_INCLUDED__

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

enum class TransformSpace
{
	World,
	Local
};

/**
 * Represents a 2D transformation used for level objects.
 * Stores local transform data and a cached world matrix.
 */
struct Transform2D
{
public:
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	float rotate = 0.0f;
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	// Cached world transformation matrix.
	glm::mat4 world;
};

#endif // __TRANSFORM_2D_H_INCLUDED__