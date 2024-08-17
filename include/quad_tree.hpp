#ifndef QUAD_H
#define QUAD_H

#include <iostream>
#include <cmath>
#include "retangulo.hpp"
#include "priority_queue.hpp"

#define INVALIDKEY -1   // Definição para chave inválida
#define INVALIDADDR -2  // Definição para endereço inválido

using quadnodekey_t = long;
using quadnodeaddr_t = long;

using quadnodekey_t = long;
using quadnodeaddr_t = long;
class QuadNode {
private:
    Retangulo _boundary;   ///< Limites do quadrante que o nó representa
    quadnodekey_t key;     ///< Chave única do nó
    quadnodeaddr_t ne;     ///< Endereço do nó filho no quadrante Nordeste
    quadnodeaddr_t nw;     ///< Endereço do nó filho no quadrante Noroeste
    quadnodeaddr_t se;     ///< Endereço do nó filho no quadrante Sudeste
    quadnodeaddr_t sw;     ///< Endereço do nó filho no quadrante Sudoeste
    Ponto *_point;         ///< Ponto armazenado neste nó, se houver

    QuadNode(Retangulo boundary = Retangulo(), quadnodekey_t key = INVALIDKEY, 
             quadnodeaddr_t ne = INVALIDADDR, quadnodeaddr_t nw = INVALIDADDR, 
             quadnodeaddr_t se = INVALIDADDR, quadnodeaddr_t sw = INVALIDADDR, 
             Ponto *ponto = nullptr);
    void reset();

    friend class QuadNodeManager;  ///< Permite que QuadNodeManager acesse membros privados
    friend class QuadTree;         ///< Permite que QuadTree acesse membros privados
};

class QuadNodeManager {
private:
    QuadNode *nodes;       ///< Vetor dinâmico de nós
    size_t _size = 0;      ///< Número atual de nós
    size_t _capacity = 0;  ///< Capacidade máxima de nós

public:
  
    void initialize(long capacity);

    quadnodeaddr_t createNode(const QuadNode &pn);
    void deleteNode(quadnodeaddr_t addr);
    QuadNode getNode(quadnodeaddr_t addr) const;
    void putNode(quadnodeaddr_t addr, QuadNode &pn);
    void destroy();
    quadnodeaddr_t localize(quadnodeaddr_t addr, const Ponto &p);

    friend class QuadTree;  ///< Permite que QuadTree acesse membros privados
};

class QuadTree
{
private:
    QuadNodeManager nodeManager; ///< Gerenciador de nós que armazena e gerencia os nós da árvore quaternária.
    quadnodeaddr_t root;         ///< Endereço do nó raiz da árvore.

public:

    QuadTree(long numNodes, Retangulo boundary);
    quadnodeaddr_t search(Ponto &p);
    quadnodeaddr_t insert(Ponto &p);

    void destroy();
    void buscaKNN(const Ponto &p, int K, PriorityQueue<Tuple<double, Ponto>> &pq) const;
    void HeuristicKNNSearch(const Ponto &p, int K, PriorityQueue<Tuple<double, Ponto>> &pq) const;
};

#endif
