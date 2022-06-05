#pragma once

#include <iomanip>
#include "../../utilities/Edge.hpp"

class NeighbourhoodList {

public:

    NeighbourhoodList(int32_t edgeNumber, int32_t vertexNumber, int32_t* data);
    ~NeighbourhoodList();
    void print();
    int32_t getVertexCount();
    int32_t getEdgeCount();
    Edge** getNeighbourhoodList();

private:
    int32_t vertexNumber;
    int32_t edgeNumber;
    Edge** neighbourhoodList;
};