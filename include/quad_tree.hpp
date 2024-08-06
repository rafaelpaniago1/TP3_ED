#ifndef QUAD_H
#define QUAD_H

#include "priority_queue.hpp"
#include "dynamic_array.hpp"
#include "retangulo.hpp"

class QuadTree {

public:
    QuadTree(Retangulo _boundary);
    ~QuadTree();
    bool insert(const Ponto& _p);
    void dividir();
    DynamicArray buscaIntervalo(Retangulo r);
    int buscaPonto(const Ponto& _p) const;
    void buscaKNN(Ponto p, int K, PriorityQueue &pq);

private:
    Retangulo l;  // Limites do quad
    Ponto p;
    DynamicArray pontos;  // Array to store points in this node
    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;

};

#endif
