#ifndef QUAD_H
#define QUAD_H
#include "retangulo.hpp"
#include "priority_queue.hpp"

class QuadTree {

public:
    
    QuadTree(Retangulo _boundary);
    bool insert(const Ponto& _p);
    void dividir();
    DynamicArray buscaIntervalo(Retangulo r);
    int buscaPonto(const Ponto& _p) const;
    void buscaKNN(Ponto p, int K, PriorityQueue &pq);

private:

    Retangulo l; //Limites do quad
    char* dados;
    Ponto p;
    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;
};

#endif