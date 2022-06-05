#pragma once

#include <iostream>

struct Edge
{
    Edge* previous;
    Edge* next;
    size_t origin;
    size_t destination;
    size_t weight;

    Edge(size_t origin, size_t destination, size_t value)
            : origin(origin), destination(destination),
              weight(value), previous(nullptr), next(nullptr) {}

    Edge() : origin(0), destination(0), weight(0),
             previous(nullptr), next(nullptr) {}

    friend std::ostream& operator<<(std::ostream& stream, const Edge& edge)
    {
        stream << edge.origin << " --> " << edge.destination << " [" << edge.weight << ']';

        return stream;
    }

    friend bool operator==(Edge const& first, Edge const& second)
    {
        return first.weight == second.weight;
    }
};
