#include "retangulo.hpp"

bool Retangulo::contemPonto(Ponto p) {
    return (p.x >= lb.x &&
    p.x <= rt.x &&
    p.y >= lb.y &&
    p.y <= rt.y);
}

Retangulo::Retangulo(Ponto lb, Ponto rt)
    : lb(lb), rt(rt) {}