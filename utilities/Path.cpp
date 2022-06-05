#include "Path.hpp"

Path::Path() : edges(), totalCost(0) {}

Path::Path(const Path& path) : edges(path.edges), totalCost(path.totalCost) { }

void Path::addEdge(PathEdge edge)
{
    this->totalCost += edge.value;
    this->edges.addFront(edge);
}

void Path::print(std::ostream& out)
{
    out << "Calkowity koszt: " << this->totalCost << std::endl;
    this->edges.print(out);
}
