#ifndef RETANGULO_H
#define RETANGULO_H
#include "math.h"
class Ponto {

public:

    double x, y;
    Ponto(double x, double y) : x(x), y(y) {}
    Ponto() : x(0), y(0) {};
    double distancia(const Ponto& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

};

class Retangulo {

public:

    Ponto lb, rt;
    Retangulo(Ponto lb, Ponto rt);
    bool contemPonto(Ponto p);
    bool intercecao(const Retangulo& other) const;

};

#endif