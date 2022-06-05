#include "BellmanFordAlgorithm.hpp"

Path BellmanFord::findShortestPath(IncidentMatrix& incidentMatrix, int32_t from, int32_t to)
{
    // Get necessary stuff from the graph
    Path result;
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgesNumer = incidentMatrix.getEdgeCount();
    int32_t* values = incidentMatrix.getEdgeValues();

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

    // Iterate V - 1 times
    for (size_t i = 0; i < vertexNumber - 1; i++)
    {
        // Iterate through all vertices
        for (size_t origin = 0; origin < vertexNumber; origin++)
        {
            // Check if vertex was visited
            if (travelCosts[origin] == INT32_MAX)
            {
                continue;
            }

            // Iterate through all edges
            for (size_t edge = 0; edge < edgesNumer; edge++)
            {
                if (matrix[origin][edge] != MatrixValues::Origin)
                {
                    continue;
                }

                // Find destination
                for (size_t destination = 0; destination < edgesNumer; destination++)
                {
                    if (matrix[destination][edge] != MatrixValues::Destination)
                    {
                        continue;
                    }

                    // Check if current travel cost is lower than old one
                    if (travelCosts[origin] + values[edge] < travelCosts[destination])
                    {
                        travelCosts[destination] = travelCosts[origin] + values[edge];
                        reachableFrom[destination] = origin;
                        reachableFor[destination] = values[edge];
                    }

                    break;
                }
            }
        }
    }

    int32_t currentVertex = to;

    // Create the shortest path
    while (currentVertex != from)
    {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}

Path BellmanFord::findShortestPath(NeighbourhoodList& neighbourhoodList, int32_t from, int32_t to)
{
    // Get necessary stuff from the graph
    Path result;
    Edge** edges = neighbourhoodList.getNeighbourhoodList();
    int32_t vertexNumber = neighbourhoodList.getVertexCount();

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

    Edge* edge = nullptr;
    // Iterate V - 1 times
    for (size_t i = 0; i < vertexNumber - 1; i++)
    {
        // Iterate through all vertices
        for (size_t j = 0; j < vertexNumber; j++)
        {
            // Check if vertex was visited
            if (travelCosts[j] == INT32_MAX)
            {
                continue;
            }

            Edge* edge = edges[j];
            while (edge != nullptr)
            {
                // Check if current travel cost is lower than old one
                if (travelCosts[j] + edge->weight < travelCosts[edge->destination])
                {
                    travelCosts[edge->destination] = travelCosts[j] + edge->weight;
                    reachableFrom[edge->destination] = j;
                    reachableFor[edge->destination] = edge->weight;
                }

                edge = edge->next;
            }
        }
    }

    int32_t currentVertex = to;

    // Create the shortest path
    while (currentVertex != from)
    {
        result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
        currentVertex = reachableFrom[currentVertex];
    }

    return result;
}
