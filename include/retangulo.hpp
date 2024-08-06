#ifndef RETANGULO_H
#define RETANGULO_H

class Ponto {

public:

    double x, y;
    Ponto(double x, double y) : x(x), y(y) {}

};

class Retangulo {

public:

    Ponto lb, rt;
    Retangulo(Ponto lb, Ponto rt);
    bool contemPonto(Ponto p);

};

#endif