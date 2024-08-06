#ifndef DYNAMIC_H
#define DYNAMIC_H
#include "retangulo.hpp"

class DynamicArray {
public:
    DynamicArray();
    ~DynamicArray();
    void push_back(const Ponto& p);
    Ponto& operator[](int index) const;
    int size() const;

private:
    Ponto* array;
    int capacity;
    int length;
    void resize(int new_capacity);
};

DynamicArray::DynamicArray() : array(nullptr), capacity(0), length(0) {}

DynamicArray::~DynamicArray() {
    delete[] array;
}

void DynamicArray::push_back(const Ponto& p) {
    if (length == capacity) {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        resize(new_capacity);
    }
    array[length++] = p;
}

Ponto& DynamicArray::operator[](int index) const {
    return array[index];
}

int DynamicArray::size() const {
    return length;
}

void DynamicArray::resize(int new_capacity) {
    Ponto* new_array = new Ponto[new_capacity];
    for (int i = 0; i < length; i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    capacity = new_capacity;
}

#endif