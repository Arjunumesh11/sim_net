#include <random>
#include <ctime>
#include <iostream>
#include "poisson.h"

std::random_device rd;
std::mt19937 gen(rd());

luint poisson(luint lambda) 
{
    std::poisson_distribution<luint> d(lambda);
    return d(gen);
}