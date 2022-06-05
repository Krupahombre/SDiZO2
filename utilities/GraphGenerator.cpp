#include "GraphGenerator.hpp"

GraphData GraphGenerator::generateRandomGraph(size_t vertexCount, float density) {

    int32_t minEdgeNumber = vertexCount;
    int32_t edgeNumber = static_cast<int32_t>((density * vertexCount * (vertexCount - 1)) / 2);
    edgeNumber = edgeNumber > minEdgeNumber ? edgeNumber : minEdgeNumber;
    int32_t dataSize = 3 * edgeNumber;
    int32_t* data = new int32_t[dataSize];
    int32_t maxValue = 10;

    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<size_t> sumOfCosts(1, maxValue);
    std::uniform_int_distribution<size_t> vertices(0, vertexCount - 1);

    bool** isThereConnection = new bool*[edgeNumber];

    for (size_t i = 0; i < edgeNumber; i++) {
        isThereConnection[i] = new bool[edgeNumber];
        for (size_t j = 0; j < edgeNumber; j++) {
            isThereConnection[i][j] = false;
        }
    }

    for (size_t i = 0; i < minEdgeNumber - 1; i++) {
        data[3 * i] = i;
        data[3 * i + 1] = i + 1;
        data[3 * i + 2] = sumOfCosts(gen);
        isThereConnection[i][i + 1] = true;
        isThereConnection[i + 1][i] = true;
    }

    data[3 * (minEdgeNumber - 1)] = minEdgeNumber - 1;
    data[3 * (minEdgeNumber - 1) + 1] = 0;
    data[3 * (minEdgeNumber - 1) + 2] = sumOfCosts(gen);
    isThereConnection[minEdgeNumber - 1][0] = true;
    isThereConnection[0][minEdgeNumber - 1] = true;

    int32_t origin;
    int32_t destination;

    for (size_t i = minEdgeNumber; i < edgeNumber; i++) {
        origin = vertices(gen);
        destination = vertices(gen);

        while (origin == destination || isThereConnection[origin][destination]) {
            origin = vertices(gen);
            destination = vertices(gen);
        }

        data[3 * i] = origin;
        data[3 * i + 1] = destination;
        data[3 * i + 2] = sumOfCosts(gen);

        isThereConnection[origin][destination] = true;
        isThereConnection[destination][origin] = true;
    }

    for (size_t i = 0; i < edgeNumber; i++) {
        delete[] isThereConnection[i];
    }
    delete[] isThereConnection;

    GraphData result;
    result.data = data;
    result.vertexCount = vertexCount;
    result.edgeCount = edgeNumber;

    return result;
}

IncidentMatrix*  GraphGenerator::generateRandomGraphAsIncidentMatrix(size_t vertexCount, float density) {

    auto graphData = generateRandomGraph(vertexCount, density);

    return new IncidentMatrix(
            graphData.edgeCount,
            graphData.vertexCount,
            graphData.data);
}

NeighbourhoodList* GraphGenerator::generateRandomGraphAsNeighbourhoodList(size_t vertexCount, float density) {

    auto graphData = generateRandomGraph(vertexCount, density);

    return new NeighbourhoodList(
            graphData.edgeCount,
            graphData.vertexCount,
            graphData.data);
}
