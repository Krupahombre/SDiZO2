#include "tests/GraphBenchmark.hpp"
#include <string>


int main(int argc, char *argv[]) {

    //np ./SDiZO_2 0.5 100 1050 MS
    const float DENSITY = std::strtof(argv[1], nullptr);
    const int VERTEX_COUNT = std::stoi(argv[2], nullptr, 10);
    const long RETRIES = std::strtol(argv[3], nullptr, 10);
    std::string timePrecision(argv[4]);
    std::transform(timePrecision.begin(), timePrecision.end(), timePrecision.begin(), tolower);

    if (timePrecision == "ns") GraphBenchmark::setPrecision(GraphBenchmark::NANOS);
    else if (timePrecision == "mi") GraphBenchmark::setPrecision(GraphBenchmark::MICROS);
    else if (timePrecision == "ms") GraphBenchmark::setPrecision(GraphBenchmark::MILIS);
    else if (timePrecision == "se") GraphBenchmark::setPrecision(GraphBenchmark::SECS);
    else GraphBenchmark::setPrecision(GraphBenchmark::NANOS);


    GraphBenchmark::setFileOutput(fopen("tests.txt", "w"));
    GraphBenchmark::setGenerateCSV(true);
    GraphBenchmark::setRetries(RETRIES);

    GraphBenchmark::primIncidentMatrix(DENSITY, VERTEX_COUNT);
    GraphBenchmark::primNeighbourhoodList(DENSITY, VERTEX_COUNT);
    GraphBenchmark::kruskalIncidentMatrix(DENSITY, VERTEX_COUNT);
    GraphBenchmark::kruskalNeighbourhoodList(DENSITY, VERTEX_COUNT);
    GraphBenchmark::dijkstraIncidentMatrix(DENSITY, VERTEX_COUNT);
    GraphBenchmark::dijkstraNeighbourhoodList(DENSITY, VERTEX_COUNT);
    GraphBenchmark::bellmanIncidentMatrix(DENSITY, VERTEX_COUNT);
    GraphBenchmark::bellmanNeighbourhoodList(DENSITY, VERTEX_COUNT);

    return 0;
}
