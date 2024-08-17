#ifndef RETANGULO_H
#define RETANGULO_H
#include "math.h"
#include <iostream>
class Ponto {

public:

    double x, y;
    std::string id;
    bool active;
    Ponto(double x = 0, double y = 0, std::string id = "", bool active = true) : x(x), y(y), id(id), active(active) {}

    double distancia(const Ponto& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    void activate()
    {
        active = true;
    }

    void deactivate()
    {
        active = false;
    }

    bool isActive() const
    {
        return active;
    }

    bool operator==(const Ponto &outro) const
    {
        return x == outro.x && y == outro.y;
    }

    std::string getId() const
    {
        return id;
    }

    double getX() const
    {
        return x;
    }
    
    double getY() const
    {
        return y;
    }

};

class Retangulo {

public:

    Ponto lb, rt;
    Retangulo();
    Retangulo(Ponto lb, Ponto rt);
    bool contemPonto(Ponto p);
    bool intercecao(const Retangulo& other) const;

    Ponto getLB() const
    {
        return lb;
    }

    Ponto getRT() const
    {
        return rt;
    }
};

#endif