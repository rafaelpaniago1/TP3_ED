#include "retangulo.hpp"

bool Retangulo::contemPonto(Ponto p) {
    return (p.x >= lb.x &&
    p.x <= rt.x &&
    p.y >= lb.y &&
    p.y <= rt.y);
}

bool Retangulo::intercecao(const Retangulo& other) const {
    return !(other.lb.x > rt.x || other.rt.x < lb.x || other.lb.y > rt.y || other.rt.y < lb.y);
}

Retangulo::Retangulo(Ponto lb, Ponto rt)
    : lb(lb), rt(rt) {}

Retangulo::Retangulo() : lb(0,0) , rt(0,0){}