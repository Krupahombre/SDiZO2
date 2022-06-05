#include "DijkstraAlgorithm.hpp"

Path Dijkstra::findShortestPath(IncidentMatrix& incidentMatrix, int32_t from, int32_t destination) {
    //Przypisanie potrzebnych danych z macierzy do lokalnych zmiennych
    Path result;
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgesNumer = incidentMatrix.getEdgeCount();
    int32_t* values = incidentMatrix.getEdgeValues();

    //Tablica informująca o tym czy wierzchołek został odwiedzony
    bool* visitedVertex = new bool[vertexNumber];

    //Zapełnienie tej tablicy
    for (size_t i = 0; i < vertexNumber; i++) {
        visitedVertex[i] = false;
    }

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
    int32_t currentVertex = from;
    int32_t unvisitedVertexNumber = vertexNumber;

    //Wykonuj dopóki istnieją nieodwiedzone wierzchołki
    while (unvisitedVertexNumber > 0) {
        //Przechodzenie przez wszystkie krawędzie
        for (size_t edge = 0; edge < edgesNumer; edge++) {
            if (matrix[currentVertex][edge] != MatrixValues::Origin) {
                continue;
            }

            //Przechodzenie przez wszystkie wierzchołki
            for (size_t vertex = 0; vertex < vertexNumber; vertex++) {
                if (matrix[vertex][edge] != MatrixValues::Destination) {
                    continue;
                }

                //Sprawdzenie czy aktualnie wygenerowany koszt podróży jest mniejszy niż ten już istniejący
                if (costOfTravelling[currentVertex] + values[edge] < costOfTravelling[vertex]) {
                    costOfTravelling[vertex] = costOfTravelling[currentVertex] + values[edge];
                    reachableFrom[vertex] = currentVertex;
                    reachableFor[vertex] = values[edge];
                }

                break;
            }
        }

        //Przypisz nowy aktualny wierzchołek
        visitedVertex[currentVertex] = true;
        unvisitedVertexNumber--;
        int32_t sortestPath = INT32_MAX;
        for (size_t vertex = 0; vertex < vertexNumber; vertex++) {
            if (visitedVertex[vertex] == false && costOfTravelling[vertex] < sortestPath) {
                sortestPath = costOfTravelling[vertex];
                currentVertex = vertex;
            }
        }
    }

    currentVertex = destination;

    //Wygenerowanie najkrótszej ścieżki
    while (currentVertex != from) {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}

Path Dijkstra::findShortestPath(NeighbourhoodList& neighbourhoodList, int32_t from, int32_t destination) {
    //Przypisanie potrzebnych danych z listy do lokalnych zmiennych
    Path result;
    Edge** edges = neighbourhoodList.getNeighbourhoodList();
    int32_t vertexNumber = neighbourhoodList.getVertexCount();

    //Tablica informująca o tym czy wierzchołek został odwiedzony
    bool* visitedVertex = new bool[vertexNumber];

    //Zapełnienie tej tablicy
    for (size_t i = 0; i < vertexNumber; i++) {
        visitedVertex[i] = false;
    }

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
    int32_t currentVertex = from;
    int32_t unvisitedVertexNumber = vertexNumber;

    //Wykonuj dopóki istnieją nieodwiedzone wierzchołki
    while (unvisitedVertexNumber > 0) {
        Edge* edge = edges[currentVertex];
        while (edge != nullptr) {
            //Sprawdzenie czy aktualnie wygenerowany koszt podróży jest mniejszy niż ten już istniejący
            if (costOfTravelling[currentVertex] + edge->weight < costOfTravelling[edge->destination]) {
                costOfTravelling[edge->destination] = costOfTravelling[currentVertex] + edge->weight;
                reachableFrom[edge->destination] = currentVertex;
                reachableFor[edge->destination] = edge->weight;
            }

            edge = edge->next;
        }

        //Przypisz nowy aktualny wierzchołek
        visitedVertex[currentVertex] = true;
        unvisitedVertexNumber--;
        int32_t sortestPath = INT32_MAX;
        for (size_t vertex = 0; vertex < vertexNumber; vertex++) {
            if (visitedVertex[vertex] == false && costOfTravelling[vertex] < sortestPath) {
                sortestPath = costOfTravelling[vertex];
                currentVertex = vertex;
            }
        }
    }

    currentVertex = destination;

    //Wygenerowanie najkrótszej ścieżki
    while (currentVertex != from) {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}
