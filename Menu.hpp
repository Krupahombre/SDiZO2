#pragma once

#include <iostream>

#include "utilities/ReaderFromFile.hpp"
#include "utilities/RandomGenerator.hpp"
#include "utilities/Timer.hpp"
#include "algorithms/Prim/PrimAlgorithm.hpp"
#include "algorithms/Kruskal/KruskalAlgorithm.hpp"
#include "algorithms/Dijkstra/DijkstraAlgorithm.hpp"
#include "algorithms/BellmanFord/BellmanFordAlgorithm.hpp"

void callPrim(IncidentMatrix* matrix, NeighbourhoodList* list) {
    auto matrixPRIM = Prim::generateMst(*matrix);

    std::cout << "---------- Macierz Incydencji - Prim MST ----------\n";

    matrixPRIM->print();
    matrixPRIM->printFancy();

    delete matrixPRIM;

    auto listPRIM = Prim::generateMst(*list);

    std::cout << "---------- Lista Sasiedztwa - Prim MST ----------\n";

    listPRIM->print();

    delete listPRIM;
}

void callKruskal(IncidentMatrix* matrix, NeighbourhoodList* list) {
    auto matrixKRUSKAL = Kruskal::generateMst(*matrix);

    std::cout << "---------- Macierz Incydencji - Kruskal MST ----------\n";

    matrixKRUSKAL->print();
    matrixKRUSKAL->printFancy();

    delete matrixKRUSKAL;

    auto listKRUSKAL = Prim::generateMst(*list);

    std::cout << "---------- Lista Sasiedztwa - Kruskal MST ----------\n";

    listKRUSKAL->print();

    delete listKRUSKAL;
}

void callDijkstra(int32_t from, int32_t destination, IncidentMatrix* matrix, NeighbourhoodList* list) {
    auto matrixDIJKSTRA = Dijkstra::findShortestPath(*matrix, from, destination);

    std::cout << "---------- Macierz Incydencji - Dijkstra SP ----------\n";

    matrixDIJKSTRA.print(std::cout);

    auto listDIJKSTRA = Dijkstra::findShortestPath(*list, from, destination);

    std::cout << "---------- Lista Sasiedztwa - Dijkstra SP ----------\n";

    listDIJKSTRA.print(std::cout);
}

void callBellmanFord(int32_t from, int32_t destination, IncidentMatrix* matrix, NeighbourhoodList* list) {
    auto matrixFORD = BellmanFord::findShortestPath(*matrix, from, destination);

    std::cout << "---------- Macierz Incydencji - Bellman-Ford SP ----------\n";

    matrixFORD.print(std::cout);

    auto listFORD = BellmanFord::findShortestPath(*list, from, destination);

    std::cout << "---------- Lista Sasiedztwa - Bellman-Ford SP ----------\n";

    listFORD.print(std::cout);
}

//menu dla mst
void mstMenu() {
    IncidentMatrix* matrix = nullptr;
    NeighbourhoodList* list = nullptr;
    GraphData graphData;
    ReaderFromFile reader;
    int userInput;

    while(true) {
        std::cout << "\nWybierz opcje:\n"
                  << "\t1. Wczytaj dane z pliku\n"
                  << "\t2. Wygeneruj graf losowo\n"
                  << "\t3. Wyswietl graf listowo i macierzowo\n"
                  << "\t4. Algorytm Prima\n"
                  << "\t5. Algorytm Kruskala\n"
                  << "\t0. Zakoncz program" << std::endl;

        std::cin >> userInput;

        switch (userInput) {
            case 1:
                if(matrix != nullptr)
                    delete matrix;

                if(list != nullptr)
                    delete list;

                matrix = reader.readerForMatrix("dane.txt");
                list = reader.readerForList("dane.txt");
                break;
            case 2:
                if(matrix != nullptr)
                    delete matrix;

                if(list != nullptr)
                    delete list;

                size_t vertexNum;
                float density;

                std::cout << "Podaj ilosc wierzcholkow: " << std::endl;
                std::cin >> vertexNum;
                std::cout << "Podaj zageszczenie (format od 0.1 do 0.99): " << std::endl;
                std::cin >> density;

                graphData = RandomGenerator::generateRandomGraph(vertexNum, density);
                matrix = new IncidentMatrix(graphData.edgeNumber, graphData.vertexNumber, graphData.data);
                list = new NeighbourhoodList(graphData.edgeNumber, graphData.vertexNumber, graphData.data);
                break;
            case 3:
                std::cout << "---------- Macierz Incydencji ----------\n";
                matrix->print();
                std::cout << std::endl << "---------- Lista Sasiedztwa ----------" << std::endl;
                list->print();
                break;
            case 4:
                callPrim(matrix, list);
                break;
            case 5:
                callKruskal(matrix, list);
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}

//menu dla najkrótszej drogi
void shortestPathMenu() {
    IncidentMatrix* matrix = nullptr;
    NeighbourhoodList* list = nullptr;
    GraphData graphData;
    ReaderFromFile reader;
    int userInput;

    while(true) {
        std::cout << "\nWybierz opcje:\n"
                  << "\t1. Wczytaj dane z pliku\n"
                  << "\t2. Wygeneruj graf losowo\n"
                  << "\t3. Wyswietl graf listowo i macierzowo\n"
                  << "\t4. Algorytm Dijkstry\n"
                  << "\t5. Algorytm Forda-Bellmana\n"
                  << "\t0. Zakoncz program" << std::endl;

        std::cin >> userInput;

        switch (userInput) {
            case 1:
                matrix = reader.readerForMatrix("dane.txt");
                list = reader.readerForList("dane.txt");
                break;
            case 2:
                size_t vertexNum;
                float density;

                std::cout << "Podaj ilosc wierzcholkow: " << std::endl;
                std::cin >> vertexNum;
                std::cout << "Podaj zageszczenie (format od 0.1 do 0.99): " << std::endl;
                std::cin >> density;

                graphData = RandomGenerator::generateRandomGraph(vertexNum, density);
                matrix = new IncidentMatrix(graphData.edgeNumber, graphData.vertexNumber, graphData.data);
                list = new NeighbourhoodList(graphData.edgeNumber, graphData.vertexNumber, graphData.data);
                break;
            case 3:
                matrix->print();
                list->print();
                break;
            case 4:
                int32_t from;
                int32_t destination;

                std::cout << "Podaj wierzcholek poczatkowy: ";
                std::cin >> from;
                std::cout << "Podaj wierzcholek docelowy: ";
                std::cin >> destination;

                callDijkstra(from, destination, matrix, list);
                break;
            case 5:
                int32_t fromA;
                int32_t destinationA;

                std::cout << "Podaj wierzcholek poczatkowy: ";
                std::cin >> fromA;
                std::cout << "Podaj wierzcholek docelowy: ";
                std::cin >> destinationA;

                callBellmanFord(fromA, destinationA, matrix, list);
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}

//główne menu
void menu() {
    int userInput;

    while(true) {
        std::cout << "\nWybierz problem do testowania:\n"
                  << "\t1. Wyznaczenie minimalnego drzewa rozpinajacego (MST)\n"
                  << "\t2. Wyznaczanie najkrotszej sciezki w grafie\n"
                  << "\t0. Zakoncz testowanie grafu" << std::endl;

        std::cin >> userInput;

        switch (userInput) {
            case 1:
                mstMenu();
                break;
            case 2:
                shortestPathMenu();
                break;
            case 0:
                return;

        }
    }
}
