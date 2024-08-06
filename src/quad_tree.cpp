#include "quad_tree.hpp"
#include "dynamic_array.hpp"

QuadTree::QuadTree(Retangulo _boundary) :
l(_boundary), p(0, 0),
northWest(nullptr),
northEast(nullptr),
southWest(nullptr),
southEast(nullptr) { }

QuadTree::~QuadTree() {
    // Desalocar memória dos quadrantes filhos
    delete northWest;
    delete northEast;
    delete southWest;
    delete southEast;
}

void QuadTree::buscaKNN(Ponto p, int K, PriorityQueue &pq) {
    if (!l.contemPonto(p)) return;

    // Iterate over points in this node
    for (int i = 0; i < pontos.size(); ++i) {
        Ponto& ponto = pontos[i];  // Remove const qualification
        double dist = p.distancia(ponto);

        if (pq.getSize() < K) {
            pq.push(&ponto, dist);
        } else if (dist < pq.peek().dis) {
            pq.pop();
            pq.push(&ponto, dist);
        }
    }

    // Recursively search in child nodes
    if (northWest != nullptr) northWest->buscaKNN(p, K, pq);
    if (northEast != nullptr) northEast->buscaKNN(p, K, pq);
    if (southWest != nullptr) southWest->buscaKNN(p, K, pq);
    if (southEast != nullptr) southEast->buscaKNN(p, K, pq);
}


DynamicArray QuadTree::buscaIntervalo(Retangulo r) {
    DynamicArray pontos;

    // If the rectangle does not intersect with the boundary, return empty list
    if (!l.intercecao(r)) {
        return pontos;
    }

    // If the point is within the rectangle, add it to the list
    if (r.contemPonto(p)) {
        pontos.push_back(p);
    }

    // If there are no subdivisions, return the points found
    if (northWest == nullptr) {
        return pontos;
    }

    // Recursively search in all subdivisions
    DynamicArray nwPoints = northWest->buscaIntervalo(r);
    for (int i = 0; i < nwPoints.size(); i++) {
        pontos.push_back(nwPoints[i]);
    }

    DynamicArray nePoints = northEast->buscaIntervalo(r);
    for (int i = 0; i < nePoints.size(); i++) {
        pontos.push_back(nePoints[i]);
    }

    DynamicArray swPoints = southWest->buscaIntervalo(r);
    for (int i = 0; i < swPoints.size(); i++) {
        pontos.push_back(swPoints[i]);
    }

    DynamicArray sePoints = southEast->buscaIntervalo(r);
    for (int i = 0; i < sePoints.size(); i++) {
        pontos.push_back(sePoints[i]);
    }

    return pontos;
}

int QuadTree::buscaPonto(const Ponto& _p) const {
    // If the current point matches, return some status or data (here we just return 1 to indicate the point is found)
    if (p.x == _p.x && p.y == _p.y) {
        return 1; // Point found
    }

    // Determine the appropriate quadrant and search recursively
    if (_p.x <= p.x && _p.y >= p.y && northWest != nullptr) {
        return northWest->buscaPonto(_p);
    } else if (_p.x <= p.x && _p.y < p.y && southWest != nullptr) {
        return southWest->buscaPonto(_p);
    } else if (_p.x >= p.x && _p.y >= p.y && northEast != nullptr) {
        return northEast->buscaPonto(_p);
    } else if (_p.x >= p.x && _p.y < p.y && southEast != nullptr) {
        return southEast->buscaPonto(_p);
    }

    return -1; // Point not found
}

void QuadTree::dividir() {

    Ponto mid(p.x, p.y);
    northWest = new QuadTree(Retangulo(Ponto(l.lb.x, mid.y),
    Ponto(mid.x, l.rt.y)));
    northEast = new QuadTree(Retangulo(mid, Ponto(l.rt.x,
    l.rt.y)));
    southWest = new QuadTree(Retangulo(Ponto(l.lb.x, l.lb.y),
    mid));
    southEast = new QuadTree(Retangulo(Ponto(mid.x, l.lb.y),
    Ponto(l.rt.x, mid.y)));

}

bool QuadTree::insert(const Ponto& _p) {

    if (!l.contemPonto(_p)) {
        return false;
    }

    if (p.x == 0 && p.y == 0) {
        p = _p;
        return true;
    }

    if (northWest == nullptr) {
        dividir();
    }

    if (northWest->insert(_p)) return true;
    if (northEast->insert(_p)) return true;
    if (southWest->insert(_p)) return true;
    if (southEast->insert(_p)) return true;

    return false;
}