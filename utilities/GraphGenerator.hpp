#pragma once

#include <random>
#include "GraphData.hpp"
#include "../structures/incidentMatrix/IncidentMatrix.hpp"
#include "../structures/neighborhoodList/NeighbourhoodList.hpp"

class GraphGenerator {
public:
    static GraphData generateRandomGraph(size_t vertexCount, float density);
    static IncidentMatrix* generateRandomGraphAsIncidentMatrix(size_t vertexCount, float density);
    static NeighbourhoodList* generateRandomGraphAsNeighbourhoodList(size_t vertexCount, float density);
};
