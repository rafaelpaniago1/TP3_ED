#ifndef PRIORITY_H
#define PRIORITY_H
#include "quad_tree.hpp"

struct Triple{

    int node;
    double dis;
    int portals;

};

class PriorityQueue{

    private:

        double* heap; //Array para armazenar o heap.
        int* indices;
        int* portals;
        int size;     //Tamanho atual do Heap
        int capacity; //Capacidade do Heap

        int parent(int i) const {return (i - 1)/2; }   //Função para encontrar o pai de um nó do heap
        int leftChild(int i) const {return (2*i+1);} //Função para encontrar o filho da esquerda do nó
        int rightChild(int i) const {return (2*i+2);}//Função para encontrar o filho da direita do nó

        void Swap(int index1, int index2);

        void HeapifyUp(int index);  //Função para manter a propriedade do Heap ao subir
        void HeapifyDown(int index);//Função para manter a propriedade do Heap ao descer

    public:

        PriorityQueue(int capacity);//Construir uma fila de prioridade de tamanho definido
        ~PriorityQueue();           //Destrutor da fila de prioridade 

        void push(double key, int index, int used);    //Função para inserir novos nós no heap
        Triple pop();        //Função para extrair o nó mínimo do 
        bool isEmpty() const;
        int getSize() const;

};

#endif