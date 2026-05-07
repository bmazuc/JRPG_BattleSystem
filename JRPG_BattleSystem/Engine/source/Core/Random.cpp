#include "Core/Random.h"

std::mt19937 Random::s_Generator;

void Random::Init()
{
	std::random_device rd;
	s_Generator.seed(rd());
}

int Random::FromRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(s_Generator);
}

float Random::FromRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(s_Generator);
}