#ifndef DYNAMIC_H
#define DYNAMIC_H
#include "dynamic_array.hpp"

DynamicArray::DynamicArray() : array(nullptr), length(0), capacity(0) {}

const Ponto& DynamicArray::operator[](int index) const {
    return array[index];
}

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

Ponto& DynamicArray::operator[](int index) {
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