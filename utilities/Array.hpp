#pragma once

#include <iostream>

template<typename T>
class Array
{
public:
    Array();
    Array(const Array<T>& array);
    ~Array();
    virtual void addFront(const T& data);
    virtual void addBack(const  T& data);
    virtual bool addAt(const size_t& index, const T& data);
    virtual bool search(const T& data);
    virtual bool removeFront();
    virtual bool removeBack();
    virtual bool removeAt(const size_t& index);
    virtual void print(std::ostream& out);
    virtual size_t getSize();
private:
    T* head;
    size_t size;
};
