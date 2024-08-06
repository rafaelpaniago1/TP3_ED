#ifndef QUAD_H
#define QUAD_H
#include "retangulo.hpp"

class QuadTree {

public:
    
    QuadTree(Retangulo _boundary);
    bool insert(const Ponto& _p);
    void dividir();
    Ponto* buscaIntervalo(Retangulo r);
    int buscaPonto(const Ponto& _p) const;
    void buscaKNN();

private:

    Retangulo l;
    char* dados;
    Ponto* p;
    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;
};

#endif