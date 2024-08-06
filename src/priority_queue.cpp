#include "priority_queue.hpp"
#include <stdexcept>
#include <iostream>

PriorityQueue::PriorityQueue(int cap) : size(0), capacity(cap) {
    heap = new double[capacity];
    indices = new int[capacity];
    portals = new int[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
    delete[] indices;
    delete[] portals;
}
    
void PriorityQueue::Swap(int index1, int index2){
    
        double temp = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = temp;
        int aux = indices[index1];
        indices[index1] = indices[index2];
        indices[index2] = aux;
        int aux2 = portals[index1];
        portals[index1] = portals[index2];
        portals[index2] = aux2;
}

void PriorityQueue::HeapifyUp(int index){

    while(index != 0 && heap[parent(index)] > heap[index]){

        int aux = parent(index);
        Swap(aux, index);
        index = aux;

    }
}

void PriorityQueue::HeapifyDown(int index) {
    
    int left = leftChild(index);
    int right = rightChild(index);

    int smallest = index;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        Swap(index, smallest);
        HeapifyDown(smallest);
    }
}

void PriorityQueue::push(double key, int index, int used){


    if (size == capacity) {
        throw "Heap is full";
    }
    heap[size] = key;
    indices[size] = index;
    portals[size] = used;
    HeapifyUp(size);
    size++;

}

bool PriorityQueue::isEmpty() const{

    return size == 0;

}

int PriorityQueue::getSize() const{

    return size;

}

Triple PriorityQueue::pop(){

    if(size == 0){

        throw "Heap is empty";

    }
    Triple minElement; 
    minElement.node = indices[0];
    minElement.dis = heap[0];
    minElement.portals = portals[0];
    Swap(0,size-1);
    size--;
    HeapifyDown(0);
    return minElement;

}