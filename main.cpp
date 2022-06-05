#include <iostream>

#include "Menu.hpp"
#include "utilities/ReaderFromFile.hpp"
#include "utilities/RandomGenerator.hpp"
#include "utilities/Timer.hpp"
#include "algorithms/Prim/PrimAlgorithm.hpp"

int main() {

/*    size_t tab[] = {
            0, 1, 2,
            0, 2, 4,
            1, 2, 2,
            1, 3, 4,
            1, 4, 2,
            2, 4, 3,
            3, 4, 3,
            3, 5, 2,
            4, 5, 2
    };*/

    ReaderFromFile reader;

    //Timer t;

    auto graphData = RandomGenerator::generateRandomGraph(8, 0.5);

    //t.stop();

    //std::cout << "\nCzas operacji: " << t.getNanos() << std::endl;

    //auto matrix = new IncidentMatrix(9, 6, tab);

   // auto matrix = reader.readerForMatrix("dane.txt");

    auto matrix = new IncidentMatrix(graphData.edgeCount, graphData.vertexCount, graphData.data);

    matrix->print();

    auto matrixPRIM = Prim::generateMst(*matrix);

    matrixPRIM->print();
    matrixPRIM->printFancy();

    delete matrix;

    //auto list = new NeighbourhoodList(9, 6, tab);

    //auto list = reader.readerForList("dane.txt");

    //auto list = new NeighbourhoodList(graphData.edgeCount, graphData.vertexCount, graphData.data);

    //list->print();

    //delete list;

    //delete[] graphData.data;

    //menu();
    return 0;
}
