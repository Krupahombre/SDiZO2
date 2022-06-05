#pragma once

#include <iostream>
#include <fstream>
#include "../structures/neighborhoodList/NeighbourhoodList.hpp"
#include "../structures/incidentMatrix/IncidentMatrix.hpp"

class ReaderFromFile {
public:
    IncidentMatrix* readerForMatrix(std::string fileName);
    NeighbourhoodList* readerForList(std::string fileName);
};
