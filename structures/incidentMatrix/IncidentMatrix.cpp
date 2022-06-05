#include "IncidentMatrix.hpp"
#include <cstdio>

IncidentMatrix::IncidentMatrix(int32_t edgeNumber, int32_t vertexNumber, int32_t* data) {
    this->vertexCount = vertexNumber; //liczba wierzchołków
    this->edgeCount = edgeNumber; //liczba krawędzi
    this->edgeValues = new int32_t[edgeNumber]; //utworzenie tablicy do przechowywania wartości poszczególnych krawędzi
    this->incidentMatrix = new MatrixValues* [vertexNumber]; //utworzenie tablicy wskaźników

    //stworzenie tablicy dwuwymiarowej i przypisanie wszędzie zer by potem wypełnić odpowiednie komórki w dalszej części kodu
    for (size_t i = 0; i < vertexNumber; i++) {
        this->incidentMatrix[i] = new MatrixValues[edgeNumber];

        for (size_t j = 0; j < edgeNumber; j++) {
            this->incidentMatrix[i][j] = MatrixValues::None;
        }
    }

    //zapełnienie odpowiednich komórek w macierzy i tablicy wartości krawędzi wartościami odczytywanymi z przesłanej struktury
    int dataIndex = 0;
    int valueIndex = 0;

    for (size_t i = 0; i < edgeNumber; i++) {
        //auto weight = data[dataIndex];
        this->incidentMatrix[data[dataIndex]][i] = MatrixValues::Origin;
        dataIndex++;
        this->incidentMatrix[data[dataIndex]][i] = MatrixValues::Destination;
        dataIndex++;
        this->edgeValues[valueIndex] = data[dataIndex];
        dataIndex++;
        valueIndex++;
    }
}

//destruktor
IncidentMatrix::~IncidentMatrix() {
    if (incidentMatrix != nullptr) {
        for (size_t i = 0; i < this->vertexCount; i++) {
            delete[] this->incidentMatrix[i];
        }
        delete[] this->incidentMatrix;
    }
}

void IncidentMatrix::print() {
    std::cout << std::endl;

    std::cout << "---------- Macierz Sasiedztwa ----------\n";

    //wyświetlenie krawędzi z wagami
    std::cout << std::endl;

    std::cout << "Wagi poszczegolnych krawedzi:\n" << std::endl;

    for (size_t i = 0; i < this->edgeCount; i++) {
        std::cout << "e" << i << ": " << std::setw(2) << this->edgeValues[i] << " | ";
        //std::setw - ustawia długość parametru drukowanego; w tym przypadku 2 miejsca
    }

    std::cout << std::endl;

//wyświetlenie macierzy
    std::cout << "\n\nUtworzona macierz incydencji:" << std::endl;

    std::cout << "\n   ";

    for (size_t i = 0; i < this->edgeCount; i++) {
        std::cout << std::setw(3) << i << "   ";
    }

    std::cout << std::endl << std::endl;

    for (size_t i = 0; i < this->vertexCount; i++) {
        std::cout << i << "  ";
        for (size_t j = 0; j < this->edgeCount; j++) {
            std::cout << std::setw(3) << int(this->incidentMatrix[i][j]) << " | ";
        }
        std::cout << std::endl;
    }
}

void printSourceNode(int32_t value, int32_t weight) {

    printf(".===.\n");
    printf("| %d |\n", value);
    printf("'==='\n\n");
    printf(" | \n");
    printf(" |  [%d] \n", weight);
    printf(" | \n");
    printf(" \\/\n");
}

void printDestinationNode(int32_t value) {

    printf("\n.===.\n");
    printf("| %d |\n", value);
    printf("'==='\n");
}

void IncidentMatrix::printFancy() {

    int32_t costOfBuildingMST = 0;
    /* Chociaż w sumie wyszło pionowo bo tak łatwiej
     *  .===.   .===.   .===.   .===.
        | a |---| b |---| c |---| d |
        '==='   '==='   '---'   '==='
     */

    std::cout<< std::endl << "---------- Macierz Sasiedztwa ----------" << std::endl;

    std::cout << "Wagi poszczegolnych krawedzi:\n" << std::endl;

    for (size_t i = 0; i < this->edgeCount; i++) {
        std::cout << "e" << i << ": " << std::setw(2) << this->edgeValues[i] << " | ";
        costOfBuildingMST += edgeValues[i];
        //std::setw - ustawia długość parametru drukowanego; w tym przypadku 2 miejsca
    }

    std::cout << "\nCalkowity koszt utworzenia MST: " << costOfBuildingMST << std::endl;

    std::cout << "\nGraf:" << std::endl;

    for (size_t i = 0; i < this->edgeCount; i++) {

        std::cout << "---------------------------" << std::endl;
        bool isSourceNodeVisited = false;
        bool delayDestinationNodePrint = false;
        int32_t delayDestinationNodeValue = 0;

        for (size_t j = 0; j < this->vertexCount; j++) {

            auto nodeType = this->incidentMatrix[j][i];

            if(nodeType == MatrixValues::Destination) {

                if(!isSourceNodeVisited) {

                    delayDestinationNodePrint = true;
                    delayDestinationNodeValue = j;
                }
                else
                    printDestinationNode(j);
            }
            else if (nodeType == MatrixValues::Origin) {

                isSourceNodeVisited = true;
                printSourceNode(j, this->edgeValues[i]);

                if(delayDestinationNodePrint) {
                    printDestinationNode(delayDestinationNodeValue);
                    delayDestinationNodePrint = false;
                }
            }
        }
        std::cout << std::endl;
    }
}

int32_t IncidentMatrix::getVertexCount() const {
    return this->vertexCount;
}

int32_t IncidentMatrix::getEdgeCount() const {
    return this-> edgeCount;
}

int32_t* IncidentMatrix::getEdgeValues() {
    return this->edgeValues;
}

MatrixValues** IncidentMatrix::getIncidentMatrix() {
    return this->incidentMatrix;
}
