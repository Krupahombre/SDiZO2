#pragma once

#include <random>
#include "GraphData.hpp"

class RandomGenerator {
public:
    static GraphData generateRandomGraph(size_t vertexNumber, float density);
};
