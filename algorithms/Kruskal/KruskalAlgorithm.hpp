#pragma once

#include "../../structures/incidentMatrix/IncidentMatrix.hpp"
#include "../../structures/neighborhoodList/NeighbourhoodList.hpp"
#include "../../utilities/EdgeHeap.hpp"

class Kruskal
{
public:
    static IncidentMatrix* generateMst(IncidentMatrix& incidentMatrix);
    static NeighbourhoodList* generateMst(NeighbourhoodList& neighbourhoodList);
};
