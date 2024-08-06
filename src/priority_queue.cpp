#include "priority_queue.hpp"
#include <stdexcept>
#include <iostream>

PriorityQueue::PriorityQueue(int cap) : size(0), capacity(cap) {
    heap = new Tuple[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}
    
void PriorityQueue::Swap(int index1, int index2) {
    std::swap(heap[index1], heap[index2]);
}

void PriorityQueue::HeapifyUp(int index) {

    while (index != 0 && heap[parent(index)].dis > heap[index].dis) {
        int aux = parent(index);
        Swap(aux, index);
        index = aux;
    }
}

void PriorityQueue::HeapifyDown(int index) {
    int left = leftChild(index);
    int right = rightChild(index);

    int smallest = index;

    if (left < size && heap[left].dis < heap[smallest].dis) {
        smallest = left;
    }
    if (right < size && heap[right].dis < heap[smallest].dis) {
        smallest = right;
    }

    if (smallest != index) {
        Swap(index, smallest);
        HeapifyDown(smallest);
    }
}

void PriorityQueue::push(Ponto* point, double distance) {
    if (size == capacity) {
        throw std::overflow_error("Heap is full");
    }
    heap[size] = {point, distance};
    HeapifyUp(size);
    size++;
}


bool PriorityQueue::isEmpty() const{

    return size == 0;

}

int PriorityQueue::getSize() const{

    return size;

}

Tuple PriorityQueue::pop() {
    if (size == 0) {
        throw std::underflow_error("Heap is empty");
    }
    Tuple minElement = heap[0];
    Swap(0, size - 1);
    size--;
    HeapifyDown(0);
    return minElement;
}

Tuple PriorityQueue::peek() const {
    if (size == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return heap[0];
}