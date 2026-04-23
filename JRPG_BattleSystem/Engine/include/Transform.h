#pragma once

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

struct Transform
{
	glm::vec2 position = glm::vec2(0, 0);
	float rotate = 0;
	glm::vec2 scale = glm::vec2(1, 1);

	glm::mat4 world;
};