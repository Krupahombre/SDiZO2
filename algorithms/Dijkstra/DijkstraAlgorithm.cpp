#include "DijkstraAlgorithm.hpp"

Path Dijkstra::findShortestPath(IncidentMatrix& incidentMatrix, int32_t from, int32_t to)
{
    // Get necessary stuff from the graph
    Path result;
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgesNumer = incidentMatrix.getEdgeCount();
    int32_t* values = incidentMatrix.getEdgeValues();

    // Create array to store information, whether vertex was visited
    bool* visitedVertices = new bool[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        visitedVertices[i] = false;
    }

    // Generate starting travel costs
    int32_t* travelCosts = new int32_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        travelCosts[i] = INT32_MAX;
    }

    // Create array to store previous vertex
    int32_t* reachableFrom = new int32_t[vertexNumber];
    // Create array to store single cost
    int32_t* reachableFor = new int32_t[vertexNumber];

    travelCosts[from] = 0;
    int32_t currentVertex = from;
    int32_t unvisitedVerticesNumber = vertexNumber;

    // Find new current vertex
    auto assignNewCurrentVertex = [&]()
    {
        visitedVertices[currentVertex] = true;
        unvisitedVerticesNumber--;
        int32_t sortestPath = INT32_MAX;
        for (size_t vertex = 0; vertex < vertexNumber; vertex++)
        {
            if (visitedVertices[vertex] == false && travelCosts[vertex] < sortestPath)
            {
                sortestPath = travelCosts[vertex];
                currentVertex = vertex;
            }
        }
    };

    // While exists unvisited vertices
    while (unvisitedVerticesNumber > 0)
    {
        // Iterate through all edges
        for (size_t edge = 0; edge < edgesNumer; edge++)
        {
            if (matrix[currentVertex][edge] != MatrixValues::Origin)
            {
                continue;
            }

            // Iterate through all vertices
            for (size_t vertex = 0; vertex < vertexNumber; vertex++)
            {
                if (matrix[vertex][edge] != MatrixValues::Destination)
                {
                    continue;
                }

                // Check if current travel cost is lower than old one
                if (travelCosts[currentVertex] + values[edge] < travelCosts[vertex])
                {
                    travelCosts[vertex] = travelCosts[currentVertex] + values[edge];
                    reachableFrom[vertex] = currentVertex;
                    reachableFor[vertex] = values[edge];
                }

                break;
            }
        }

        // Assing new current vetrex
        assignNewCurrentVertex();
    }

    currentVertex = to;

    // Create the shortest path
    while (currentVertex != from)
    {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}

Path Dijkstra::findShortestPath(NeighbourhoodList& neighbourhoodList, int32_t from, int32_t to)
{
    // Get necessary stuff from the graph
    Path result;
    Edge** edges = neighbourhoodList.getNeighbourhoodList();
    int32_t vertexNumber = neighbourhoodList.getVertexCount();

    // Create array to store information, whether vertex was visited
    bool* visitedVertices = new bool[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        visitedVertices[i] = false;
    }

    // Generate starting travel costs
    int32_t* travelCosts = new int32_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        travelCosts[i] = INT32_MAX;
    }

    // Create array to store previous vertex
    int32_t* reachableFrom = new int32_t[vertexNumber];
    // Create array to store single cost
    int32_t* reachableFor = new int32_t[vertexNumber];

    travelCosts[from] = 0;
    int32_t currentVertex = from;
    int32_t unvisitedVerticesNumber = vertexNumber;

    // Find new current vertex
    auto assignNewCurrentVertex = [&]()
    {
        visitedVertices[currentVertex] = true;
        unvisitedVerticesNumber--;
        int32_t sortestPath = INT32_MAX;
        for (size_t vertex = 0; vertex < vertexNumber; vertex++)
        {
            if (visitedVertices[vertex] == false && travelCosts[vertex] < sortestPath)
            {
                sortestPath = travelCosts[vertex];
                currentVertex = vertex;
            }
        }
    };

    // While exists unvisited vertices
    while (unvisitedVerticesNumber > 0)
    {
        Edge* edge = edges[currentVertex];
        while (edge != nullptr)
        {
            // Check if current travel cost is lower than old one
            if (travelCosts[currentVertex] + edge->weight < travelCosts[edge->destination])
            {
                travelCosts[edge->destination] = travelCosts[currentVertex] + edge->weight;
                reachableFrom[edge->destination] = currentVertex;
                reachableFor[edge->destination] = edge->weight;
            }

            edge = edge->next;
        }

        // Assing new current vetrex
        assignNewCurrentVertex();
    }

    currentVertex = to;

    // Create the shortest path
    while (currentVertex != from)
    {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}
