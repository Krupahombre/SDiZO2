#include "PrimAlgorithm.hpp"

//mst dla prima zawsze zaczynam od wierzchołka zerowego

IncidentMatrix* Prim::generateMst(IncidentMatrix& incidentMatrix) {
    //Przypisanie potrzebnych danych z macierzy do lokalnych zmiennych
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgeNumber = incidentMatrix.getEdgeCount();
    int32_t * values = incidentMatrix.getEdgeValues();
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();

    //Zmienne potrzebne do zbierania rozwiązań z algorytmu
    int32_t resultSize = (vertexNumber - 1) * 3; //rozmiar dostosowany do danych jakie przyjmuje dana struktura w konstruktorze, podobne do odczytu z pliku
    int32_t* bufforForResultData = new int32_t[resultSize];
    int32_t resultIndex = 0;
    EdgeHeap* heap = new EdgeHeap();

    //Tablica z informacją czy dany wierzchołek został już odwiedzony
    bool* visitedVertex = new bool[vertexNumber];

    //Zapełnienie tej tablicy
    for (size_t i = 0; i < vertexNumber; i++) {
        visitedVertex[i] = false;
    }

    //zmienna oznaczająca od jakiego wierzchołka idziemy oraz t tablicy odwiedzonych wierzchołków dajemy true
    size_t currentVertexIndex = 0;
    visitedVertex[currentVertexIndex] = true;

    //Dodanie wszytkich wierzchołków na stack (kopiec)
    for (size_t begin = 0; begin < edgeNumber; begin++) {
        if (matrix[currentVertexIndex][begin] == MatrixValues::None) {
            continue;
        }

        //Poszukiwanie końca
        for (size_t end = 0; end < vertexNumber; end++) {
            if (matrix[end][begin] == MatrixValues::None || end == currentVertexIndex) {
                continue;
            }

            if (visitedVertex[end]) {
                continue;
            }

            //Wrzucenie krawędzi na stack
            heap->push(new Edge(currentVertexIndex, end, values[begin]));
        }

    }

    //Iterowanie przez wszystkie krawędzie dostępne na kopcu w celu wyszukania odpowiednich połączeń oraz zapisania wyników
    for (size_t i = 0; i < vertexNumber - 1;) {
        Edge* candidate = heap->pop();

        //Sprawdzenie czy miejsce docelowe krawędzi zostało odwiedzone; wychodzimy od pierwszego elemenu ściągniętego ze stacka
        if (!visitedVertex[candidate->destination]) {
            //Zapisanie wyników algorytmu
            currentVertexIndex = candidate->destination;
            bufforForResultData[3 * resultIndex] = candidate->origin;
            bufforForResultData[3 * resultIndex + 1] = candidate->destination;
            bufforForResultData[3 * resultIndex + 2] = candidate->weight;
            visitedVertex[currentVertexIndex] = true;

            //dodanie pozostałych wierzchołków na stack (kopiec)
            for (size_t begin = 0; begin < edgeNumber; begin++) {
                if (matrix[currentVertexIndex][begin] == MatrixValues::None) {
                    continue;
                }

                //Poszukiwanie końca
                for (size_t end = 0; end < vertexNumber; end++) {
                    if (matrix[end][begin] == MatrixValues::None || end == currentVertexIndex) {
                        continue;
                    }

                    if (visitedVertex[end]) {
                        continue;
                    }

                    //Wrzucenie krawędzi na stack
                    heap->push(new Edge(currentVertexIndex, end, values[begin]));
                }
            }

            resultIndex++;
            i++;
        }

        delete candidate;
    }

    // Utworzenie wynikowej macierzy by można było ją zwrócić
    IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, bufforForResultData);
    delete[] bufforForResultData;
    delete heap;

    return result;
}

NeighbourhoodList* Prim::generateMst(NeighbourhoodList& neighbourhoodList) {
    //Przypisanie potrzebnych danych z listy do lokalnych zmiennych
    int32_t vertexNumber = neighbourhoodList.getVertexCount();

    //zmienne potrzebne do zbierania rozwiązań z algorytmu
    int32_t resultSize = (vertexNumber - 1) * 3; //rozmiar dostosowany do danych jakie przyjmuje dana struktura w konstruktorze, podobne do odczytu z pliku
    int32_t* bufforForResultData = new int32_t[resultSize];
    int32_t resultIndex = 0;
    Edge** edgesList = neighbourhoodList.getNeighbourhoodList();
    EdgeHeap* heap = new EdgeHeap(false);

    //Tablica z informacją czy dany wierzchołek został już odwiedzony
    bool* visitedVertex = new bool[vertexNumber];

    //Zapełnienie tej tablicy
    for (size_t i = 0; i < vertexNumber; i++) {
        visitedVertex[i] = false;
    }

    //zmienna oznaczająca od jakiego wierzchołka idziemy oraz dla tablicy odwiedzonych wierzchołków dajemy true
    size_t currentVertexIndex = 0;
    visitedVertex[currentVertexIndex] = true;

    //Dodanie wszytkich wierzchołków na stack (kopiec)
    for (size_t i = 0; i < vertexNumber; i++) {
        Edge* edge = edgesList[i];

        if (edge == nullptr) {
            continue;
        }

        while (edge != nullptr) {
            //Sprawdzenie czy źródłowe pochodzenie krawęzi zostało odwiedzone
            if (edge->origin == currentVertexIndex && !visitedVertex[edge->destination]) {
                heap->push(edge);
            }

            //Sprawdzenie czy docelowa miejsce krawędzi nie zostało odwiedzone
            if (edge->destination == currentVertexIndex && !visitedVertex[edge->origin]) {
                heap->push(edge);
            }

            edge = edge->next;
        }
    }

    //Iterowanie przez wszytskie krawędzie
    for (size_t i = 0; i < vertexNumber - 1;) {
        Edge* candidate = heap->pop();

        //Sprawdzenie czy punkt startowy i docelowy krawędzi nie zostały odwiedzone
        if (!visitedVertex[candidate->destination] || !visitedVertex[candidate->origin]) {
            //Wybranie nowego aktualnego wierzchołka
            currentVertexIndex = visitedVertex[candidate->destination]
                                 ? candidate->origin
                                 : candidate->destination;

            //Zapisanie wyników algorytmu
            bufforForResultData[3 * resultIndex] = candidate->origin;
            bufforForResultData[3 * resultIndex + 1] = candidate->destination;
            bufforForResultData[3 * resultIndex + 2] = candidate->weight;
            visitedVertex[currentVertexIndex] = true;

            for (size_t i = 0; i < vertexNumber; i++) {
                Edge* edge = edgesList[i];

                if (edge == nullptr) {
                    continue;
                }

                while (edge != nullptr) {
                    //Sprawdzenie czy źródłowe pochodzenie krawęzi zostało odwiedzone
                    if (edge->origin == currentVertexIndex && !visitedVertex[edge->destination]) {
                        heap->push(edge);
                    }

                    //Sprawdzenie czy docelowa miejsce krawędzi nie zostało odwiedzone
                    if (edge->destination == currentVertexIndex && !visitedVertex[edge->origin]) {
                        heap->push(edge);
                    }

                    edge = edge->next;
                }
            }

            resultIndex++;
            i++;
        }
    }

    //Utworzenie wynikowej listy by można było ją zwrócić
    NeighbourhoodList* result = new NeighbourhoodList(vertexNumber - 1, vertexNumber, bufforForResultData);
    delete[] bufforForResultData;
    delete heap;

    return result;
}