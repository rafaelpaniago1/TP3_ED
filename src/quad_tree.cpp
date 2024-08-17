#include "quad_tree.hpp"
#include <algorithm>

QuadNode::QuadNode(Retangulo boundary, quadnodekey_t key, quadnodeaddr_t ne, quadnodeaddr_t nw, quadnodeaddr_t se, quadnodeaddr_t sw, Ponto *ponto) : _boundary(boundary), key(INVALIDKEY), ne(ne), nw(nw), se(se), sw(sw), _point(ponto)
{
}

void QuadNode::reset()
{
    key = INVALIDKEY;
    ne = nw = se = sw = INVALIDADDR;
    _point = nullptr;
}

quadnodeaddr_t QuadNodeManager::createNode(const QuadNode &pn)
{
    nodes[_size++] = pn;
    return _size - 1; // Retorna o índice do novo nó
}

void QuadNodeManager::deleteNode(quadnodeaddr_t addr)
{
    if (addr >= 0 && static_cast<size_t>(addr) < _size)
    {
        nodes[addr].reset();
    }
}

void QuadNodeManager::putNode(quadnodeaddr_t addr, QuadNode &pn)
{
    if (addr >= 0 && static_cast<size_t>(addr) < _size)
    {
        pn.key = addr;
        nodes[addr] = pn;
    }
}

QuadNode QuadNodeManager::getNode(quadnodeaddr_t addr) const
{
    if (addr >= 0 && static_cast<size_t>(addr) < _size)
    {
        return nodes[addr];
    }
    return QuadNode(Retangulo(Ponto(0, 0), Ponto(0, 0)));
}

void QuadNodeManager::initialize(long capacity)
{
    _capacity = capacity;
    nodes = new QuadNode[_capacity];
}

void QuadNodeManager::destroy()
{
    delete[] nodes;
}

quadnodeaddr_t QuadNodeManager::localize(quadnodeaddr_t addr, const Ponto &p)
{
    QuadNode nx = getNode(addr);
    Retangulo _boundary = nx._boundary;
    Ponto *_point = nx._point;
    Ponto mid(_point->getX(), _point->getY());

    Retangulo neRet = Retangulo(mid, Ponto(_boundary.getRT().getX(), _boundary.getRT().getY()));
    Retangulo nwRet = Retangulo(Ponto(_boundary.getLB().getX(), mid.getY()), Ponto(mid.getX(), _boundary.getRT().getY()));
    Retangulo swRet = Retangulo(Ponto(_boundary.getLB().getX(), _boundary.getLB().getY()), mid);
    Retangulo seRet = Retangulo(Ponto(mid.getX(), _boundary.getLB().getY()), Ponto(_boundary.getRT().getX(), mid.getY()));

    if (_boundary.contemPonto(p))
    {
        if (neRet.contemPonto(p))
        {
            if (nodes[addr].ne == INVALIDADDR)
            {
                nodes[addr].ne = createNode(QuadNode(neRet));
            }
            return nodes[addr].ne;
        }
        else if (nwRet.contemPonto(p))
        {
            if (nodes[addr].nw == INVALIDADDR)
            {
                nodes[addr].nw = createNode(QuadNode(nwRet));
            }
            return nodes[addr].nw;
        }
        else if (swRet.contemPonto(p))
        {
            if (nodes[addr].sw == INVALIDADDR)
            {
                nodes[addr].sw = createNode(QuadNode(swRet));
            }
            return nodes[addr].sw;
        }
        else if (seRet.contemPonto(p))
        {
            if (nodes[addr].se == INVALIDADDR)
            {
                nodes[addr].se = createNode(QuadNode(seRet));
            }
            return nodes[addr].se;
        }
    }
    return INVALIDADDR;
}
QuadTree::QuadTree(long numNodes, Retangulo boundary) : root(0)
{
    nodeManager.initialize(numNodes);
    QuadNode root_node(boundary, 0, INVALIDADDR, INVALIDADDR, INVALIDADDR, INVALIDADDR, nullptr);
    nodeManager.createNode(root_node);
}

quadnodeaddr_t QuadTree::search(Ponto &p)
{
    // Implementação da busca pela chave k na QuadTree baseada em (x, y)
    // (Detalhes da lógica de busca dependem da divisão espacial)
    return INVALIDADDR;
}

quadnodeaddr_t QuadTree::insert(Ponto &p)
{

    quadnodeaddr_t current = root;

    while (true)
    {
        QuadNode currentNode = nodeManager.getNode(current);

        if (!currentNode._boundary.contemPonto(p))
        {
            return INVALIDADDR;
        }
        if (currentNode._point == nullptr)
        {
            currentNode._point = &p;
            nodeManager.putNode(current, currentNode);
            return current;
        }
        else
        {
            current = nodeManager.localize(current, p);
        }
    }
}

void QuadTree::destroy()
{
    nodeManager.destroy();
}

double heuristic(const Ponto &p, const Retangulo &box)
{

    double xMin = box.getLB().getX();
    double xMax = box.getRT().getX();
    double yMin = box.getLB().getY();
    double yMax = box.getRT().getY();

    Ponto center((xMin + xMax) / 2.0, (yMin + yMax) / 2.0);
    Ponto bottomLeft(xMin, yMin);
    Ponto bottomRight(xMax, yMin);
    Ponto topLeft(xMin, yMax);
    Ponto topRight(xMax, yMax);

    double distCenter = p.distancia(center);
    double distBottomLeft = p.distancia(bottomLeft);
    double distBottomRight = p.distancia(bottomRight);
    double distTopLeft = p.distancia(topLeft);
    double distTopRight = p.distancia(topRight);

    return std::min({distBottomLeft, distBottomRight, distTopLeft, distTopRight, distCenter});
}

void QuadTree::buscaKNN(const Ponto &p, int K, PriorityQueue<Tuple<double, Ponto>> &pq) const
{
    for(int i = 0; i < nodeManager._size; i++){
        QuadNode currentNode = nodeManager.getNode(i);
        if(currentNode._point != nullptr){
            double dist = currentNode._point->distancia(p);
            Tuple<double, Ponto> d(dist, *currentNode._point);
            if(currentNode._point->isActive()){
                if(pq.getSize() < K){
                    pq.push(d);
                }else if(dist < pq.peek().getFirst()){
                    pq.pop();
                    pq.push(d);
                }
            }
        }
    }
}

void QuadTree::HeuristicKNNSearch(const Ponto &p, int K, PriorityQueue<Tuple<double, Ponto>> &pq) const
{
    PriorityQueue<Tuple<double, quadnodeaddr_t>> pq_aux(nodeManager._capacity / 2, true);
    pq_aux.push(Tuple<double, quadnodeaddr_t>(0, root));

    size_t visited = 0;
    int stagnated = 0;
    while (!pq_aux.isEmpty() && (stagnated <= nodeManager._capacity / 10 || pq.getSize() < K))
    {
        quadnodeaddr_t current = pq_aux.peek().getSecond();

        pq_aux.pop();

        QuadNode currentNode = nodeManager.getNode(current);

        if (!currentNode._boundary.contemPonto(p))
        {
            continue;
        }
        visited++;

        const Ponto *ponto = currentNode._point;

        if (ponto != nullptr)
        {
            double dist = ponto->distancia(p);

            Tuple<double, Ponto> d(dist, *ponto);
            if (ponto->isActive())
            {
                if (pq.getSize() < K)
                {

                    pq.push(d);
                    stagnated = 0;
                }
                else if (dist < pq.peek().getFirst())
                {

                    pq.pop();
                    pq.push(d);
                    stagnated = 0;
                }
                else
                {
                    stagnated++;
                }
            }

            if (currentNode.ne != INVALIDADDR)
            {
                double heuristicDist = heuristic(p, nodeManager.getNode(currentNode.ne)._boundary);
                try
                {
                    pq_aux.push(Tuple<double, quadnodeaddr_t>(heuristicDist, currentNode.ne));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            if (currentNode.nw != INVALIDADDR)
            {
                double heuristicDist = heuristic(p, nodeManager.getNode(currentNode.nw)._boundary);
                try
                {
                    pq_aux.push(Tuple<double, quadnodeaddr_t>(heuristicDist, currentNode.nw));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            if (currentNode.sw != INVALIDADDR)
            {
                double heuristicDist = heuristic(p, nodeManager.getNode(currentNode.sw)._boundary);
                try
                {
                    pq_aux.push(Tuple<double, quadnodeaddr_t>(heuristicDist, currentNode.sw));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            if (currentNode.se != INVALIDADDR)
            {
                double heuristicDist = heuristic(p, nodeManager.getNode(currentNode.se)._boundary);
                try
                {
                    pq_aux.push(Tuple<double, quadnodeaddr_t>(heuristicDist, currentNode.se));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
    }

}
