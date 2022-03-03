#ifndef UTILITY_H
#define UTILITY_H

#include <random>

double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
#endif