#ifndef __TRANSFORM_2D_H_INCLUDED__
#define __TRANSFORM_2D_H_INCLUDED__

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

enum class TransformSpace
{
	World,
	Local
};

struct Transform2D
{
	glm::vec2 position = glm::vec2(0, 0);
	float rotate = 0;
	glm::vec2 scale = glm::vec2(1, 1);

	glm::mat4 world;
};

#endif // __TRANSFORM_2D_H_INCLUDED__