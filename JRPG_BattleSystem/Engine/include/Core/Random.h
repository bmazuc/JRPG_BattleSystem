#ifndef __RANDOM_H_INCLUDED__
#define __RANDOM_H_INCLUDED__

#include <random>

/**
 * Utility class providing random number generation helpers.
 */
class Random
{
public:
	/**
	 * Initializes the random number generator.
	 */
	static void Init();

	/**
	 * Returns a random integer within the specified range.
	 */
	static int FromRange(int min, int max);
	/**
	 * Returns a random float within the specified range.
	 */
	static float FromRange(float min, float max);

	template<typename T>
	static void ShuffleVector(std::vector<T>& v)
	{
		std::shuffle(v.begin(), v.end(), s_Generator);
	}

private:
	// Shared random number generator instance.
	static std::mt19937 s_Generator;
};

#endif // __RANDOM_H_INCLUDED__