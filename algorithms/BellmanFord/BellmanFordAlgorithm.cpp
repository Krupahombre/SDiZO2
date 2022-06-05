#include "BellmanFordAlgorithm.hpp"

Path BellmanFord::findShortestPath(IncidentMatrix& incidentMatrix, int32_t from, int32_t destination) {
    //Przypisanie potrzebnych danych z macierzy do lokalnych zmiennych
    Path result;
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgesNumer = incidentMatrix.getEdgeCount();
    int32_t* values = incidentMatrix.getEdgeValues();

    //Wygenerowanie tablicy która przechowuje koszt przejścia do danego wierzchołka
    //Początkowo przypisujemy największą możliwą wartość
    int32_t* costOfTravelling = new int32_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++) {
        costOfTravelling[i] = INT32_MAX;
    }

    //Utworzenie tablic do przechowywania poprzedniego wierzchołka
    int32_t* reachableFrom = new int32_t[vertexNumber];
    //Tablica przechowująca koszt dojścia do danego wierzchołka
    int32_t* reachableFor = new int32_t[vertexNumber];

    costOfTravelling[from] = 0;

    //Iterowanie dopóki są wierzchołki
    for (size_t i = 0; i < vertexNumber - 1; i++) {
        //Przechodzenie przez wszystkie wierzchołki
        for (size_t origin = 0; origin < vertexNumber; origin++) {
            //Sprawdzenie czy wierzchołek był odwiedzony
            if (costOfTravelling[origin] == INT32_MAX) {
                continue;
            }

            //Iterowanie przez wszystkie krawędzie
            for (size_t edge = 0; edge < edgesNumer; edge++) {
                if (matrix[origin][edge] != MatrixValues::Origin) {
                    continue;
                }

                //Szukanie celu
                for (size_t destination = 0; destination < edgesNumer; destination++) {
                    if (matrix[destination][edge] != MatrixValues::Destination) {
                        continue;
                    }

                    //Sprawdzenie czy aktualnie wygenerowany koszt podróży jest mniejszy niż ten już istniejący
                    if (costOfTravelling[origin] + values[edge] < costOfTravelling[destination]) {
                        costOfTravelling[destination] = costOfTravelling[origin] + values[edge];
                        reachableFrom[destination] = origin;
                        reachableFor[destination] = values[edge];
                    }

                    break;
                }
            }
        }
    }

    int32_t currentVertex = destination;

    //Wygenerowanie najkrótszej ścieżki
    while (currentVertex != from) {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}

Path BellmanFord::findShortestPath(NeighbourhoodList& neighbourhoodList, int32_t from, int32_t destination) {
    //Przypisanie potrzebnych danych z listy do lokalnych zmiennych
    Path result;
    Edge** edges = neighbourhoodList.getNeighbourhoodList();
    int32_t vertexNumber = neighbourhoodList.getVertexCount();

    //Wygenerowanie tablicy która przechowuje koszt przejścia do danego wierzchołka
    //Początkowo przypisujemy największą możliwą wartość
    int32_t* costOfTravelling = new int32_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++) {
        costOfTravelling[i] = INT32_MAX;
    }

    //Utworzenie tablic do przechowywania poprzedniego wierzchołka
    int32_t* reachableFrom = new int32_t[vertexNumber];
    //Tablica przechowująca koszt dojścia do danego wierzchołka
    int32_t* reachableFor = new int32_t[vertexNumber];

    costOfTravelling[from] = 0;

    Edge* edge = nullptr;
    //Iterowanie dopóki są wierzchołki
    for (size_t i = 0; i < vertexNumber - 1; i++) {
        //Przechodzenie przez wszystkie wierzchołki
        for (size_t j = 0; j < vertexNumber; j++) {
            //Sprawdzenie czy wierzchołek został odwiedzony
            if (costOfTravelling[j] == INT32_MAX) {
                continue;
            }

            Edge* edge = edges[j];
            while (edge != nullptr) {
                //Sprawdzenie czy aktualnie wygenerowany koszt podróży jest mniejszy niż ten już istniejący
                if (costOfTravelling[j] + edge->weight < costOfTravelling[edge->destination]) {
                    costOfTravelling[edge->destination] = costOfTravelling[j] + edge->weight;
                    reachableFrom[edge->destination] = j;
                    reachableFor[edge->destination] = edge->weight;
                }

                edge = edge->next;
            }
        }
    }

    int32_t currentVertex = destination;

    //Wygenerowanie najkrótszej ścieżki
    while (currentVertex != from) {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}
