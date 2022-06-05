#include "KruskalAlgorithm.hpp"

IncidentMatrix* Kruskal::generateMst(IncidentMatrix& incidentMatrix)
{
    // Get necessary stuff from the graph
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgeNumber = incidentMatrix.getEdgeCount();
    int32_t* values = incidentMatrix.getEdgeValues();
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();
    int32_t resultSize = (vertexNumber - 1) * 3;
    int32_t* resultBuffor = new int32_t[resultSize];
    size_t resultIndex = 0;
    EdgeHeap* heap = new EdgeHeap();

    // Assign unique ids to every tree
    size_t* treeIds = new size_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        treeIds[i] = i;
    }

    Edge* buffor = nullptr;
    // Iterate through all edges
    for (size_t edge = 0; edge < edgeNumber; edge++)
    {
        buffor = new Edge(-1, -1, values[edge]);

        // Iterate through all vertices and add them to the heap
        for (size_t vertex = 0; vertex < vertexNumber; vertex++)
        {
            if (matrix[vertex][edge] == MatrixValues::Origin)
            {
                buffor->origin = vertex;
            }

            if (matrix[vertex][edge] == MatrixValues::Destination)
            {
                buffor->destination = vertex;
            }
        }

        heap->push(buffor);
    }

    while (!heap->isEmpty())
    {
        buffor = heap->pop();

        // Check if tree ids are different
        if (treeIds[buffor->origin] != treeIds[buffor->destination])
        {
            // Add edge to the result
            resultBuffor[3 * resultIndex] = buffor->origin;
            resultBuffor[3 * resultIndex + 1] = buffor->destination;
            resultBuffor[3 * resultIndex + 2] = buffor->weight;

            // Correct tree ids
            int oldTreeId = treeIds[buffor->origin];
            int newTreeId = treeIds[buffor->destination];
            for (size_t id = 0; id < vertexNumber; id++)
            {
                if (treeIds[id] == oldTreeId)
                {
                    treeIds[id] = newTreeId;
                }
            }

            resultIndex++;
        }
    }

    // Create result tree
    IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, resultBuffor);
    delete[] resultBuffor;
    delete heap;

    return result;
}

NeighbourhoodList* Kruskal::generateMst(NeighbourhoodList& neighbourhoodList)
{
    // Get necessary stuff from the graph
    int32_t vertexNumber = neighbourhoodList.getVertexCount();
    int32_t resultSize = (vertexNumber - 1) * 3;
    int32_t* resultBuffor = new int32_t[resultSize];
    size_t resultIndex = 0;
    Edge** edges = neighbourhoodList.getNeighbourhoodList();
    EdgeHeap* heap = new EdgeHeap(false);

    // Assign unique ids to every tree
    size_t* treeIds = new size_t[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        treeIds[i] = i;
    }

    Edge* buffor = nullptr;
    // Iterate through all vertices and add them to the heap
    for (size_t vertex = 0; vertex < vertexNumber; vertex++)
    {
        buffor = edges[vertex];

        while (buffor != nullptr)
        {
            heap->push(buffor);
            buffor = buffor->next;
        }
    }

    while (!heap->isEmpty())
    {
        buffor = heap->pop();

        // Check if tree ids are different
        if (treeIds[buffor->origin] != treeIds[buffor->destination])
        {
            // Add edge to the result
            resultBuffor[3 * resultIndex] = buffor->origin;
            resultBuffor[3 * resultIndex + 1] = buffor->destination;
            resultBuffor[3 * resultIndex + 2] = buffor->weight;

            // Correct tree ids
            int oldTreeId = treeIds[buffor->origin];
            int newTreeId = treeIds[buffor->destination];
            for (size_t id = 0; id < vertexNumber; id++)
            {
                if (treeIds[id] == oldTreeId)
                    treeIds[id] = newTreeId;
            }

            resultIndex++;
        }
    }

    // Create result tree
    NeighbourhoodList* result = new NeighbourhoodList(vertexNumber - 1, vertexNumber, resultBuffor);
    delete[] resultBuffor;
    delete heap;

    return result;
}
