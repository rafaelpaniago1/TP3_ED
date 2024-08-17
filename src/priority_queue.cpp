#include "priority_queue.hpp"
#include <stdexcept>
#include <iostream>
    
template <typename K>
void PriorityQueue<K>::swap(K &a, K &b)
{
    K temp = a;
    a = b;
    b = temp;
}

template <typename K>
void PriorityQueue<K>::HeapifyUp(int index)
{
    if (modo)
    {
        if (index && heap[parent(index)] > heap[index])
        {
            swap(heap[index], heap[parent(index)]);
            HeapifyUp(parent(index));
        }
    }
    else
    {
        if (index && heap[parent(index)] < heap[index])
        {
            swap(heap[index], heap[parent(index)]);
            HeapifyUp(parent(index));
        }
    }
}

template <typename K>
void PriorityQueue<K>::HeapifyDown(int index)
{
    if (modo)
    {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index)
        {
            swap(heap[index], heap[smallest]);
            HeapifyDown(smallest);
        }
    }
    else
    {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            HeapifyDown(largest);
        }
    }
}

template <typename K>
void PriorityQueue<K>::push(K data) {
    if (size == capacity) {
        throw std::overflow_error("Heap is full");
    }
    heap[0] = data; 
    HeapifyUp(size);
    size++;
}


template <typename K>
bool PriorityQueue<K>::isEmpty() const
{
    return size == 0;
}

template <typename K>
int PriorityQueue<K>::getSize() const{

    return size;

}

template <typename K>
void PriorityQueue<K>::pop()
{
    if (size <= 0)
    {
        throw std::underflow_error("Priority Queue is empty.");
    }
    heap[0] = heap[--size];
    HeapifyDown(0);
}

template <typename K>
K PriorityQueue<K>::peek() const {
    if (size <= 0) {
        throw std::underflow_error("Heap is empty");
    }
    return heap[0];
}

template <typename K>
int PriorityQueue<K>::parent(int index) const{ return (index - 1) / 2; }

template <typename K>
int PriorityQueue<K>::leftChild(int index) const{ return (2 * index + 1); }

template <typename K>
int PriorityQueue<K>::rightChild(int index) const{ return (2 * index + 2); }

template <typename K>
PriorityQueue<K>::PriorityQueue(int capacity, bool mode) : size(0), capacity(capacity), modo(mode)
{
    heap = new K[capacity];
}

template <typename K>
PriorityQueue<K>::~PriorityQueue()
{
    delete[] heap;
}

template <typename K>
void PriorityQueue<K>::mudarModo()
{
    modo = !modo;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        HeapifyDown(i);
    }
}