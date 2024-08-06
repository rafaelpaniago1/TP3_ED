#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "retangulo.hpp"

class DynamicArray {
public:
    DynamicArray();
    ~DynamicArray();
    void push_back(const Ponto& p);
    Ponto& operator[](int index);
    const Ponto& operator[](int index) const;
    int size() const;
private:
    void resize(int newCapacity);
    Ponto* array;
    int length;
    int capacity;
};

#endif
