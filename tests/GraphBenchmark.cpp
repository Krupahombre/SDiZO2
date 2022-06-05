#include "GraphBenchmark.hpp"
#include "../utilities/GraphGenerator.hpp"
#include "../algorithms/Prim/PrimAlgorithm.hpp"
#include "../algorithms/Kruskal/KruskalAlgorithm.hpp"
#include "../algorithms/Dijkstra/DijkstraAlgorithm.hpp"
#include "../algorithms/BellmanFord/BellmanFordAlgorithm.hpp"

long GraphBenchmark::lowRandom = 0;
long GraphBenchmark::highRandom = 100;
long GraphBenchmark::retries = 100;
FILE* GraphBenchmark::file = nullptr;
bool GraphBenchmark::generateCSV = false;
const std::string GraphBenchmark::resultDecorator = "[------------------------------------------------------------------]\n";
GraphBenchmark::Precision GraphBenchmark::printPrecision = GraphBenchmark::Precision::NANOS;

void GraphBenchmark::primIncidentMatrix(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsIncidentMatrix(vertexCount, density);

        Timer timer;
        Prim::generateMst(*matrix);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("primIncidentMatrix", vertexCount, density, times);
}

void GraphBenchmark::primNeighbourhoodList(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsNeighbourhoodList(vertexCount, density);

        Timer timer;
        Prim::generateMst(*matrix);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("primNeighbourhoodList", vertexCount, density, times);
}

void GraphBenchmark::kruskalIncidentMatrix(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsIncidentMatrix(vertexCount, density);

        Timer timer;
        Kruskal::generateMst(*matrix);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("kruskalIncidentMatrix", vertexCount, density, times);
}

void GraphBenchmark::kruskalNeighbourhoodList(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsNeighbourhoodList(vertexCount, density);

        Timer timer;
        Kruskal::generateMst(*matrix);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("kruskalNeighbourhoodList", vertexCount, density, times);
}

void GraphBenchmark::dijkstraIncidentMatrix(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsIncidentMatrix(vertexCount, density);

        Timer timer;
        Dijkstra::findShortestPath(*matrix, 0, vertexCount - 1);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("dijkstraIncidentMatrix", vertexCount, density, times);
}

void GraphBenchmark::dijkstraNeighbourhoodList(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsNeighbourhoodList(vertexCount, density);

        Timer timer;
        Dijkstra::findShortestPath(*matrix, 0, vertexCount - 1);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("dijkstraNeighbourhoodList", vertexCount, density, times);
}

void GraphBenchmark::bellmanIncidentMatrix(float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsIncidentMatrix(vertexCount, density);

        Timer timer;
        BellmanFord::findShortestPath(*matrix, 0, vertexCount - 1);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("bellmanIncidentMatrix", vertexCount, density, times);
}

void GraphBenchmark::bellmanNeighbourhoodList( float density, int vertexCount) {

    std::vector<long> times(retries);

    for (int i = 0; i < retries; ++i) {

        auto matrix = GraphGenerator::generateRandomGraphAsNeighbourhoodList(vertexCount, density);

        Timer timer;
        BellmanFord::findShortestPath(*matrix, 0, vertexCount - 1);
        timer.stop();

        times.push_back(getMatchingTimeResult(timer));

        delete matrix;
    }

    autoPrintBenchResults("bellmanNeighbourhoodList", vertexCount, density, times);
}
