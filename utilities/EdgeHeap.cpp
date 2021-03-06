#include "EdgeHeap.hpp"

EdgeHeap::EdgeHeap(bool clearOnDelete) {

    this->clearOnDelete = clearOnDelete;
    this->size = 0;
    this->root = nullptr;
}

EdgeHeap::~EdgeHeap() {
    // Check if size is 0
    if (this->size == 0) {
        return;
    }

    // Check if clear flag is set
    if (this->clearOnDelete) {
        // Delete edges
        for (size_t i = 0; i < this->size; i++) {
            delete this->root[i];
        }
    }

    // Delete root
    delete[] this->root;
}

void EdgeHeap::push(Edge* edge)
{
    // Check if size is 0
    if (this->size == 0)
    {
        // Create new root
        this->size++;
        this->root = new Edge * [this->size];
        this->root[0] = edge;
        return;
    }

    // Copy existing edges
    Edge** buffor = new Edge * [this->size + 1];
    for (size_t i = 0; i < this->size; i++)
    {
        buffor[i] = this->root[i];
    }

    // Delete old root and change references
    delete[] this->root;
    this->root = buffor;
    this->root[size] = edge;
    this->size++;

    // Fix heap struture
    this->fixUp();
}

Edge* EdgeHeap::pop()
{
    // Chech if size is 0
    if (this->size == 0)
    {
        return nullptr;
    }

    // Select first edge
    Edge* edgeToReturn = this->root[0];

    // Check if size is 1
    if (this->size == 1)
    {
        // Delete root
        this->size--;
        delete[] this->root;
        this->root = nullptr;

        // Return edge
        return edgeToReturn;
    }

    // Copy last leaf to first position
    this->root[0] = this->root[this->size - 1];
    this->size--;

    // Create buffor
    Edge** buffor = new Edge * [this->size];

    // Copy existing edges
    for (size_t i = 0; i < this->size; i++)
    {
        buffor[i] = this->root[i];
    }

    // Delete root and change  references
    delete[] this->root;
    this->root = buffor;

    // Fix heap struture
    this->fixDown();

    // Return edge
    return edgeToReturn;
}

bool EdgeHeap::isEmpty()
{
    if (this->size == 0)
    {
        return true;
    }

    return false;
}

void EdgeHeap::print()
{
    for (size_t i = 0; i < this->size; i++)
    {
        std::cout << this->root[i]->origin << ' ' << this->root[i]->destination << ' ' << this->root[i]->weight << std::endl;
    }
}

void EdgeHeap::fixUp()
{
    int i = this->size - 1;
    int parent = (i - 1) / 2;
    Edge* buffor = nullptr;

    while (this->root[parent]->weight > this->root[i]->weight)
    {
        buffor = root[parent];

        this->root[parent] = this->root[i];
        this->root[i] = buffor;

        i = parent;
        parent = (i - 1) / 2;
    }
}

void EdgeHeap::fixDown()
{
    int i = 0;
    int j = 2 * i + 1;
    Edge* buffor = nullptr;

    while (j < this->size)
    {
        if (j + 1 < this->size && this->root[j]->weight > this->root[j + 1]->weight)
        {
            j += 1;
        }

        if (this->root[i]->weight <= this->root[j]->weight)
        {
            break;
        }

        buffor = this->root[i];
        this->root[i] = this->root[j];
        this->root[j] = buffor;
        i = j;
        j = 2 * i + 1;
    }
}
