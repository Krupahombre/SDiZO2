#pragma once

#include <iostream>
#include <iomanip>
#include "../../utilities/Enums.hpp"

class IncidentMatrix {

public:
    IncidentMatrix(int32_t edgeNumber, int32_t vertexNumber, int32_t* data);
    ~IncidentMatrix();
    void print();
    void printFancy();
    int32_t getVertexCount() const;
    int32_t getEdgeCount() const;
    int32_t* getEdgeValues();
    MatrixValues** getIncidentMatrix();

private:
    int32_t vertexCount;
    int32_t edgeCount;
    int32_t * edgeValues;
    MatrixValues** incidentMatrix;
};
