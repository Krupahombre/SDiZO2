#pragma once

#include "../../structures/incidentMatrix/IncidentMatrix.hpp"
#include "../../structures/neighborhoodList/NeighbourhoodList.hpp"
#include "../../utilities/Path.hpp"
#include "../../utilities/PathEdge.hpp"

class BellmanFord
{
public:
    static Path findShortestPath(IncidentMatrix& incidentMatrix, int32_t from, int32_t dest);
    static Path findShortestPath(NeighbourhoodList& neighbourhoodList, int32_t from, int32_t dest);
};
