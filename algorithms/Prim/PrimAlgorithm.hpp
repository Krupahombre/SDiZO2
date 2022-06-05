#pragma once

#include "../../structures/incidentMatrix/IncidentMatrix.hpp"
#include "../../structures/neighborhoodList/NeighbourhoodList.hpp"
#include "../../utilities/EdgeHeap.hpp"
#include "../../utilities/Edge.hpp"

class Prim
{
public:
    static IncidentMatrix* generateMst(IncidentMatrix& incidentMatrix);
    static NeighbourhoodList* generateMst(NeighbourhoodList& neighbourhoodList);
};
