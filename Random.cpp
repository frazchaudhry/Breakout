#include "stdafx.h"
#include "Random.h"

// Returns a random number in [low, high].
int Random(int low, int high)
{
	return low + rand() % ((high + 1) - low);
}