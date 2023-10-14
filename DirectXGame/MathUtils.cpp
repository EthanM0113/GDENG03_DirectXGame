#include "MathUtils.h"

#include <ctime>
#include <stdlib.h>

float MathUtils::randomFloat(float a, float b)
{
    float random = a + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (b - a)));
    return random;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}