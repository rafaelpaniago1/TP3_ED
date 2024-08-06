#ifndef PRIORITY_H
#define PRIORITY_H
#include "quad_tree.hpp"

struct Tuple{

    Ponto* point;
    double dis;

};

class PriorityQueue{

    private:

        Tuple* heap; //Array para armazenar o heap.
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
        PriorityQueue(const PriorityQueue&) = delete;
        PriorityQueue& operator=(const PriorityQueue&) = delete;

        void push(Ponto* point, double distance);    //Função para inserir novos nós no heap
        Tuple pop();        //Função para extrair o nó mínimo do 
        bool isEmpty() const;
        int getSize() const;
        Tuple peek() const;

};

#endif