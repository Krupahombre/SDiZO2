#include "PrimAlgorithm.hpp"

IncidentMatrix* Prim::generateMst(IncidentMatrix& incidentMatrix)
{
    int32_t vertexNumber = incidentMatrix.getVertexCount();
    int32_t edgeNumber = incidentMatrix.getEdgeCount();
    int32_t * values = incidentMatrix.getEdgeValues();
    MatrixValues** matrix = incidentMatrix.getIncidentMatrix();
    int32_t resultSize = (vertexNumber - 1) * 3;
    int32_t* resultBuffor = new int32_t[resultSize];
    int32_t resultIndex = 0;
    EdgeHeap* heap = new EdgeHeap();

    // Tablica z informacją czy dany wierzchołek został już odwiedzony
    bool* visitedVertices = new bool[vertexNumber];

    for (size_t i = 0; i < vertexNumber; i++)
    {
        visitedVertices[i] = false;
    }

    size_t currentVertexIndex;

    // Push edges that can be reached to the heap
    auto pushReachableEdges = [&]()
    {
        // Iterate through all edges to find begin
        for (size_t begin = 0; begin < edgeNumber; begin++)
        {
            if (matrix[currentVertexIndex][begin] == MatrixValues::None)
            {
                continue;
            }

            // Iterate through all vertices to find end
            for (size_t end = 0; end < vertexNumber; end++)
            {
                if (matrix[end][begin] == MatrixValues::None || end == currentVertexIndex)
                {
                    continue;
                }

                if (visitedVertices[end])
                {
                    continue;
                }

                // Push edge to the heap
                heap->push(new Edge(currentVertexIndex, end, values[begin]));
            }

        }
    };

    // Set initial states
    currentVertexIndex = 0;
    visitedVertices[currentVertexIndex] = true;
    pushReachableEdges();

    // Iterate through all vertices
    for (size_t i = 0; i < vertexNumber - 1;)
    {
        Edge* candidate = heap->pop();

        // Check if destination of edge from top of heap was visited
        if (!visitedVertices[candidate->destination])
        {
            // Save results
            currentVertexIndex = candidate->destination;
            resultBuffor[3 * resultIndex] = candidate->origin;
            resultBuffor[3 * resultIndex + 1] = candidate->destination;
            resultBuffor[3 * resultIndex + 2] = candidate->weight;
            visitedVertices[currentVertexIndex] = true;
            pushReachableEdges();
            resultIndex++;
            i++;
        }

        delete candidate;
    }

    // Create result tree
    IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, resultBuffor);
    delete[] resultBuffor;
    delete heap;

    return result;
}

NeighbourhoodList* Prim::generateMst(NeighbourhoodList& neighbourhoodList)
{
    // Get necessary stuff from the graph
    int32_t vertexNumber = neighbourhoodList.getVertexCount();
    int32_t resultSize = (vertexNumber - 1) * 3;
    int32_t* resultBuffor = new int32_t[resultSize];
    int32_t resultIndex = 0;
    Edge** edgesList = neighbourhoodList.getNeighbourhoodList();
    EdgeHeap* heap = new EdgeHeap(false);

    // Create array to store information, whether vertex was visited
    bool* visitedVertices = new bool[vertexNumber];
    for (size_t i = 0; i < vertexNumber; i++)
    {
        visitedVertices[i] = false;
    }

    size_t currentVertexIndex;

    // Push edgesList that can be reached to the heap
    auto pushReachableEdges = [&]()
    {
        // Iterate through all edgesList to find begin
        for (size_t i = 0; i < vertexNumber; i++)
        {
            Edge* edge = edgesList[i];

            if (edge == nullptr)
            {
                continue;
            }

            while (edge != nullptr)
            {
                // Check if origin of the edge was not visited
                if (edge->origin == currentVertexIndex && !visitedVertices[edge->destination])
                {
                    heap->push(edge);
                }

                // Check if destination of the edge was not visited
                if (edge->destination == currentVertexIndex && !visitedVertices[edge->origin])
                {
                    heap->push(edge);
                }

                edge = edge->next;
            }
        }
    };

    // Set initial states
    currentVertexIndex = 0;
    visitedVertices[currentVertexIndex] = true;
    pushReachableEdges();

    // Iterate through all vertices
    for (size_t i = 0; i < vertexNumber - 1;)
    {
        Edge* candidate = heap->pop();

        // Check if origin or destination of the edge is not visited
        if (!visitedVertices[candidate->destination] || !visitedVertices[candidate->origin])
        {
            // Select new current vertex
            currentVertexIndex = visitedVertices[candidate->destination]
                                 ? candidate->origin
                                 : candidate->destination;

            // Save the result
            resultBuffor[3 * resultIndex] = candidate->origin;
            resultBuffor[3 * resultIndex + 1] = candidate->destination;
            resultBuffor[3 * resultIndex + 2] = candidate->weight;
            visitedVertices[currentVertexIndex] = true;
            pushReachableEdges();
            resultIndex++;
            i++;
        }
    }

    // Create result tree
    NeighbourhoodList* result = new NeighbourhoodList(vertexNumber - 1, vertexNumber, resultBuffor);
    delete[] resultBuffor;
    delete heap;

    return result;
}