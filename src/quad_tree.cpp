#include "quad_tree.hpp"

QuadTree::QuadTree(Retangulo _boundary) :
l(_boundary), p(0, 0),
northWest(nullptr),
northEast(nullptr),
southWest(nullptr),
southEast(nullptr) { }

void QuadTree::buscaKNN(){

    

}

Ponto* QuadTree::buscaIntervalo(Retangulo r) {

    vector<Ponto> pontos; // lista vazia
    if (!l.intercecao(r)) { return pontos; // se não há interseção
    } else {
    if (r.contemPonto(p)) pontos.push_back(p);
    }
    if (northwest == NULL) return pontos;
    pontos.push_back(northwest->buscaPonto(r));
    pontos.push_back(northeast->buscaPonto(r));
    pontos.push_back(southwest->buscaPonto(r));
    pontos.push_back(southeast->buscaPonto(r));
    return pontos;

}

int QuadTree::buscaPonto(const Ponto& _p) const {

    if (p != nullptr && *_p == *p) return dados;
    if (_p.x <= p->x && _p.y >= p->y && northWest != nullptr)
    return northWest->buscaPonto(_p);
    else if (_p.x <= p->x && _p.y < p->y && southWest != nullptr)
    return southWest->buscaPonto(_p);
    else if (_p.x >= p->x && _p.y >= p->y && northEast != nullptr)
    return northEast->buscaPonto(_p);
    else if (_p.x >= p->x && _p.y < p->y && southEast != nullptr)
    return southEast->buscaPonto(_p);
    return -1; // O ponto não foi encontrado

}

void QuadTree::dividir() {

    Ponto mid(p->x, p->y);
    northWest = new QuadTree(Retangulo(Ponto(limites.lb.x, mid.y),
    Ponto(mid.x, limites.rt.y)));
    northEast = new QuadTree(Retangulo(mid, Ponto(limites.rt.x,
    limites.rt.y)));
    southWest = new QuadTree(Retangulo(Ponto(limites.lb.x, limites.lb.y),
    mid));
    southEast = new QuadTree(Retangulo(Ponto(mid.x, limites.lb.y),
    Ponto(limites.rt.x, mid.y)));

}

bool QuadTree::insert(const Ponto& _p) {
    
    if (!limites.contemPonto(_p)) return false;
    // Se o ponto está vazio
    if (_p == nullptr) {
        _p = new Ponto(_p);
        return true;
    }
    // Senão, subdividir e tentar inserir nos demais
    if (northWest == nullptr) dividir();
    if (northWest->insert(_p)) return true;
    else if (northEast->insert(_p)) return true;
    else if (southWest->insert(_p)) return true;
    else if (southEast->insert(_p)) return true;
    return false;

}