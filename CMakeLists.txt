cmake_minimum_required(VERSION 3.22)
project(SDiZO_2)

set(CMAKE_CXX_STANDARD 23)

add_executable(SDiZO_2 main.cpp Menu.hpp structures/incidentMatrix/IncidentMatrix.cpp structures/incidentMatrix/IncidentMatrix.hpp utilities/Enums.hpp structures/neighborhoodList/NeighbourhoodList.cpp structures/neighborhoodList/NeighbourhoodList.hpp utilities/ReaderFromFile.cpp utilities/ReaderFromFile.hpp utilities/GraphGenerator.cpp utilities/GraphGenerator.hpp utilities/GraphData.hpp utilities/Timer.hpp algorithms/Prim/PrimAlgorithm.cpp algorithms/Prim/PrimAlgorithm.hpp algorithms/Kruskal/KruskalAlgorithm.cpp algorithms/Kruskal/KruskalAlgorithm.hpp algorithms/Dijkstra/DijkstraAlgorithm.cpp algorithms/Dijkstra/DijkstraAlgorithm.hpp algorithms/BellmanFord/BellmanFordAlgorithm.cpp algorithms/BellmanFord/BellmanFordAlgorithm.hpp utilities/Array.cpp utilities/Array.hpp utilities/Edge.hpp utilities/EdgeHeap.cpp utilities/EdgeHeap.hpp utilities/Path.cpp utilities/Path.hpp utilities/PathEdge.hpp tests/GraphBenchmark.hpp tests/GraphBenchmark.cpp)
SET(GCC_COMPILE_FLAGS "-O3 -static-libgcc -static-libstdc++")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")