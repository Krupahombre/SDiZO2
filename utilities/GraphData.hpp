#pragma once

#include <iomanip>

struct GraphData
{
    GraphData(const GraphData& graphData)
            : data(graphData.data), vertexNumber(graphData.vertexNumber),
              edgeNumber(graphData.edgeNumber) {}

    GraphData() : data(nullptr), vertexNumber(0), edgeNumber(0) {}

    int32_t* data;
    int32_t vertexNumber;
    int32_t edgeNumber;
};
