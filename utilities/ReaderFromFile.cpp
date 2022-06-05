#include "ReaderFromFile.hpp"

//odczytywanie dla macierzy
IncidentMatrix* ReaderFromFile::readerForMatrix(std::string fileName) {
    int32_t edgeNumber;
    int32_t vertexNumber;
    int32_t* data;

    //otworzenie pliku do odczytania
    std::ifstream file(fileName);

    //odczytanie z pierwszej linii ilości krawędzi oraz ilości wierzchołków
    file >> edgeNumber >> vertexNumber;

    //utworzenie tablicy o rozmiarze 3 krotnie większym niż ilość krawędzi, ponieważ w każdej linijce pliku tekstowego są 3 wartości
    data = new int32_t[edgeNumber*3];

    //odczytywanie całej zawartości pliku i wpisywanie do tablicy
    for(size_t i = 0; i < edgeNumber*3; i++)
        file >> data[i];

    //utworzenie obiektu struktury z zebranych danych
    IncidentMatrix* matrix = new IncidentMatrix(edgeNumber, vertexNumber, data);

    delete[] data;

    return matrix;
}

//odczytywanie dla listy jest tanalogiczne do odczytywania dla macierzy
NeighbourhoodList* ReaderFromFile::readerForList(std::string fileName) {
    int32_t edgeNumber;
    int32_t vertexNumber;
    int32_t* data;

    std::ifstream file(fileName);

    file >> edgeNumber >> vertexNumber;

    data = new int32_t[edgeNumber*3];

    for(size_t i = 0; i < edgeNumber*3; i++)
        file >> data[i];

    NeighbourhoodList* list = new NeighbourhoodList(edgeNumber, vertexNumber, data);

    delete[] data;

    return list;
}
