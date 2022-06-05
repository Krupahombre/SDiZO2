#include <iostream>
#include "NeighbourhoodList.hpp"

NeighbourhoodList::NeighbourhoodList(int32_t edgeNumber, int32_t vertexNumber, int32_t* data) {
    this->edgeNumber = edgeNumber;
    this->vertexNumber = vertexNumber;
    this->neighbourhoodList = new Edge* [vertexNumber];

    for (size_t i = 0; i < vertexNumber; i++)
    {
        this->neighbourhoodList[i] = nullptr;
    }

    Edge* edge = nullptr;
    size_t dataNumber = 3 * edgeNumber;
    size_t currentIndex = 0;

    while (currentIndex < dataNumber)
    {
        auto test = data[currentIndex];
        edge = this->neighbourhoodList[data[currentIndex]];

        if (edge == nullptr)
        {
            this->neighbourhoodList[data[currentIndex]] = new Edge(data[currentIndex], data[currentIndex + 1], data[currentIndex + 2]);
            currentIndex += 3;
            continue;
        }

        while (edge->next != nullptr)
        {
            edge = edge->next;
        }

        edge->next = new Edge(data[currentIndex], data[currentIndex + 1], data[currentIndex + 2]);
        edge->next->previous = edge;
        currentIndex += 3;
    }
}

//destruktor
NeighbourhoodList::~NeighbourhoodList() {
    if (this->neighbourhoodList != nullptr)
    {
        Edge* edgeToDelete = nullptr;
        for (size_t i = 0; i < this->vertexNumber; i++)
        {
            edgeToDelete = this->neighbourhoodList[i];

            if (edgeToDelete == nullptr)
            {
                continue;
            }

            while (edgeToDelete->next != nullptr)
            {
                edgeToDelete = edgeToDelete->next;
                delete edgeToDelete->previous;
            }
            delete edgeToDelete;
        }
        delete[] this->neighbourhoodList;
    }
}

void NeighbourhoodList::print() {

//    std::cout << std::endl << "---------- Lista Sasiedztwa ----------" << std::endl;
    std::cout << std::endl << "Utworzona lista sasiedztwa:\n" << std::endl;

    for(size_t i = 0; i < this->vertexNumber; i++) {
        std::cout << "W[" << i << "]:";
        auto currentEdge = this->neighbourhoodList[i];

        while(currentEdge != nullptr) {
            std::cout << "--> W[" << currentEdge->destination << "] koszt = " << std::setw(2) << currentEdge->weight << "| ";
            currentEdge = currentEdge->next;
        }

        std::cout << std::endl;
    }
}

int32_t NeighbourhoodList::getVertexCount() {
    return this->vertexNumber;
}

int32_t NeighbourhoodList::getEdgeCount() {
    return this->edgeNumber;
}

Edge** NeighbourhoodList::getNeighbourhoodList() {
    return this->neighbourhoodList;
}
