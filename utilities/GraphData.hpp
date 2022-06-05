#pragma once

#include <iomanip>

struct GraphData
{
    GraphData(const GraphData& graphData)
            : data(graphData.data), vertexCount(graphData.vertexCount),
              edgeCount(graphData.edgeCount) {}

    GraphData() : data(nullptr), vertexCount(0), edgeCount(0) {}

    int32_t* data;
    int32_t vertexCount;
    int32_t edgeCount;
};
