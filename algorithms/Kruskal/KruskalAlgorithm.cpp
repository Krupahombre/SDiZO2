#include "KruskalAlgorithm.hpp"

IncidentMatrix* Kruskal::generateMst(IncidentMatrix& incidentMatrix) {
    //Przypisanie potrzebnych danych z macierzy do lokalnych zmiennych
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgeNumber = incidentMatrix.getEdgeCount();
    int32_t* values = incidentMatrix.getEdgeValues();
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();

    //Zmienne potrzebne do zbierania rozwiązań z algorytmu
    int32_t resultSize = (vertexNumber - 1) * 3; //rozmiar dostosowany do danych jakie przyjmuje dana struktura w konstruktorze, podobne do odczytu z pliku
    int32_t* bufforForResultData = new int32_t[resultSize];
    size_t resultIndex = 0;
    EdgeHeap* heap = new EdgeHeap();

    //Tablica odwzorowująca ułożenie wierzchołków rosnąco
    size_t* vertexConnectionID = new size_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++) {
        vertexConnectionID[i] = i;
    }

    Edge* buffor = nullptr;
    //Iterowanie przez wszystkie krawędzie
    for (size_t edge = 0; edge < edgeNumber; edge++) {
        buffor = new Edge(-1, -1, values[edge]);

        //Iterowanie przez wszystkie wierzchołki i dodanie je do kopca
        for (size_t vertex = 0; vertex < vertexNumber; vertex++) {
            if (matrix[vertex][edge] == MatrixValues::Origin) {
                buffor->origin = vertex;
            }

            if (matrix[vertex][edge] == MatrixValues::Destination) {
                buffor->destination = vertex;
            }
        }

        //Wrzucanie do kopca
        heap->push(buffor);
    }

    //iteruj dopóki kopiec nie jest pusty
    while (!heap->isEmpty()) {
        //zdjęcie elementu z góry kopca
        buffor = heap->pop();

        //Sprawdzenie czy dla poszczególnych wierzchołków ID jest różne
        if (vertexConnectionID[buffor->origin] != vertexConnectionID[buffor->destination]) {
            //Dodanie danych do rozwiązania
            bufforForResultData[3 * resultIndex] = buffor->origin;
            bufforForResultData[3 * resultIndex + 1] = buffor->destination;
            bufforForResultData[3 * resultIndex + 2] = buffor->weight;

            //Poprawienie ID połączeń
            int oldConnectionID = vertexConnectionID[buffor->origin];
            int newConnectionID = vertexConnectionID[buffor->destination];
            for (size_t id = 0; id < vertexNumber; id++) {
                if (vertexConnectionID[id] == oldConnectionID) {
                    vertexConnectionID[id] = newConnectionID;
                }
            }

            resultIndex++;
        }
    }

    //Utworzenie wynikowej macierzy, która utworzy nam MST
    IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, bufforForResultData);
    delete[] bufforForResultData;
    delete heap;

    return result;
}

NeighbourhoodList* Kruskal::generateMst(NeighbourhoodList& neighbourhoodList) {
    //Przypisanie potrzebnych danych z macierzy do lokalnych zmiennych
    int32_t vertexNumber = neighbourhoodList.getVertexCount();

    //Zmienne potrzebne do zbierania rozwiązań z algorytmu
    int32_t resultSize = (vertexNumber - 1) * 3; //rozmiar dostosowany do danych jakie przyjmuje dana struktura w konstruktorze, podobne do odczytu z pliku
    int32_t* bufforForResultData = new int32_t[resultSize];
    size_t resultIndex = 0;
    Edge** edges = neighbourhoodList.getNeighbourhoodList();
    EdgeHeap* heap = new EdgeHeap(false);

    //Tablica odwzorowująca ułożenie wierzchołków rosnąco
    size_t* vertexConnectionID = new size_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++) {
        vertexConnectionID[i] = i;
    }

    Edge* buffor = nullptr;
    //Iterowanie przez wszystkie krawędzie i dodanie ich do kopca
    for (size_t vertex = 0; vertex < vertexNumber; vertex++) {
        buffor = edges[vertex];

        while (buffor != nullptr) {
            heap->push(buffor);
            buffor = buffor->next;
        }
    }

    while (!heap->isEmpty()) {
        buffor = heap->pop();

        //Sprawdzenie czy dla poszczególnych połączeń wierzchołków ID jest różne
        if (vertexConnectionID[buffor->origin] != vertexConnectionID[buffor->destination]) {
            //Dodanie danych do rozwiązania
            bufforForResultData[3 * resultIndex] = buffor->origin;
            bufforForResultData[3 * resultIndex + 1] = buffor->destination;
            bufforForResultData[3 * resultIndex + 2] = buffor->weight;

            //Poprawienie ID połączeń
            int oldConnectionID = vertexConnectionID[buffor->origin];
            int newConnectionID = vertexConnectionID[buffor->destination];
            for (size_t id = 0; id < vertexNumber; id++)
            {
                if (vertexConnectionID[id] == oldConnectionID)
                    vertexConnectionID[id] = newConnectionID;
            }

            resultIndex++;
        }
    }

    //Utworzenie wynikowej listy, która utworzy nam MST
    NeighbourhoodList* result = new NeighbourhoodList(vertexNumber - 1, vertexNumber, bufforForResultData);
    delete[] bufforForResultData;
    delete heap;

    return result;
}
