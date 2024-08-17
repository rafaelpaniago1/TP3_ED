#ifndef PRIORITY_H
#define PRIORITY_H
#include "retangulo.hpp"

template <typename one, typename two>
class Tuple {
public:

    Tuple() : first(one()), second(two()) {}

    Tuple(const one &first, const two &second) : first(first), second(second) {}

    one getFirst() const {
        return first;
    }
    two getSecond() const {
        return second;
    }
    void setFirst(const one &value) {
        first = value;
    }
    void setSecond(const two &value) {
        second = value;
    }
    bool operator==(const Tuple &compare) const {
        return first == compare.first && second == compare.second;
    }
    bool operator!=(const Tuple &compare) const {
        return !(*this == compare);
    }
    bool operator<(const Tuple &compare) const {
        return first < compare.first;
    }
    bool operator>(const Tuple &compare) const {
        return first > compare.first;
    }
    bool operator<=(const Tuple &compare) const {
        return !(*this > compare);
    }
    bool operator>=(const Tuple &compare) const {
        return !(*this < compare);
    }

private:
    one first;
    two second; 
};

template class Tuple<double, Ponto>;
template class Tuple<double, long>;
template class Tuple<double, int>;

template <typename K>

class PriorityQueue{

    private:

        K* heap; //Array para armazenar o heap.
        int size;     //Tamanho atual do Heap
        int capacity; //Capacidade do Heap
        bool modo;

        int parent(int index) const;   //Função para encontrar o pai de um nó do heap
        int leftChild(int index) const;
        int rightChild(int index) const;

        void swap(int index1, int index2);

        void HeapifyUp(int index);  //Função para manter a propriedade do Heap ao subir
        void HeapifyDown(int index);//Função para manter a propriedade do Heap ao descer

    public:

        void mudarModo();
        PriorityQueue(int capacity = 15000, bool mode = false);
        ~PriorityQueue();           //Destrutor da fila de prioridade 

        void push(K data);  
        K peek() const; 
        void pop();        //Função para extrair o nó mínimo do 
        bool isEmpty() const;
        int getSize() const;
    
};

#endif