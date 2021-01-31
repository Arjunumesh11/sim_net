#include <random>
#include <ctime>
#include <iostream>
#include "poisson.h"

luint poisson(luint lambda)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::poisson_distribution<luint> d(lambda);
    return d(gen);
}