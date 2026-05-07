#ifndef __RANDOM_H_INCLUDED__
#define __RANDOM_H_INCLUDED__

#include <random>

class Random
{
public:
	static void Init();

	static int FromRange(int min, int max);
	static float FromRange(float min, float max);

private:
	static std::mt19937 s_Generator;
};

#endif // __RANDOM_H_INCLUDED__