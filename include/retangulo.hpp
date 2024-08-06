#ifndef RETANGULO_H
#define RETANGULO_H

class Ponto {

public:

    double x, y;
    Ponto(double x, double y) : x(x), y(y) {}
    Ponto() : x(0), y(0) {};

};

class Retangulo {

public:

    Ponto lb, rt;
    Retangulo(Ponto lb, Ponto rt);
    bool contemPonto(Ponto p);
    bool intercecao(const Retangulo& other) const;

};

#endif