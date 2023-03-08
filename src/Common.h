#ifndef __COMMON_H__
#define __COMMON_H__

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <ostream>
#include <random>
#include <type_traits>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double DegreesToRadians(double degrees)
{
    return degrees * pi / 180.;
}

inline double RandomDouble()
{
    return rand() / (RAND_MAX + 1.);
}

inline double RandomDouble(double min, double max)
{
    return min + (max - min) * RandomDouble();
}

inline double RandomDoubleGenerator()
{
    static std::uniform_int_distribution<> distribution(.0, 1.);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double Clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

#endif // __COMMON_H__