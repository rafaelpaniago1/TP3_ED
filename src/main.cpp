#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstring>   
#include "quad_tree.hpp"
#include "endereco.hpp"
#include "hash_table.hpp"

Hash<std::string, Endereco> *loadFile(std::ifstream &inputFile, int NumEnderecos, QuadTree &quadTree)
{
    Hash<std::string, Endereco> *estacoes = new Hash<std::string, Endereco>(NumEnderecos);

    std::string line;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string idend, sid_logrado, sigla_tipo, nome_logra, numero_imo, nome_bairr, nome_regio, scep, sx, sy;
        double x, y;
        int cep;
        long id_logradouro;

        if (std::getline(iss, idend, ';') &&
            std::getline(iss, sid_logrado, ';') &&
            std::getline(iss, sigla_tipo, ';') &&
            std::getline(iss, nome_logra, ';') &&
            std::getline(iss, numero_imo, ';') &&
            std::getline(iss, nome_bairr, ';') &&
            std::getline(iss, nome_regio, ';') &&
            std::getline(iss, scep, ';') &&
            std::getline(iss, sx, ';') &&
            std::getline(iss, sy, ';'))
        {
            id_logradouro = std::stol(sid_logrado);
            cep = std::stoi(scep);
            x = std::stod(sx);
            y = std::stod(sy);

            Ponto *ponto = new Ponto(x, y, idend);
            Endereco *estacao = new Endereco(*ponto, idend, id_logradouro, sigla_tipo, nome_logra, numero_imo, nome_bairr, nome_regio, cep);
            quadTree.insert(*ponto);
            estacoes->insert(idend, estacao);
        }
    }
    inputFile.close();

    return estacoes;
}

void consultar(QuadTree &quadTree, Hash<std::string, Endereco> &estacoes, double x, double y, int n)
{

    Ponto p(x, y);
    PriorityQueue<Tuple<double, Ponto>> pq(n);
    quadTree.buscaKNN(p, n, pq);

    pq.mudarModo();
    while (!pq.isEmpty())
    {
        Tuple<double, Ponto> p = pq.peek();
        pq.pop();

        double dist = p.getFirst();
        std::string id = p.getSecond().getId();
        Endereco *estacao = estacoes.search(id);

        if (estacao != nullptr)
        {
            std::cout << *estacao << std::fixed << std::setprecision(3) << " (" << dist << ")" << std::endl;
        }
    }
}

void ativar(QuadTree &quadTree, Hash<std::string, Endereco> &estacoes, int numEnderecos, std::string id)
{
    Endereco *estacao = estacoes.search(id);
    if (estacao == nullptr)
    {
        std::cout << "Ponto de recarga " << id << " não encontrado." << std::endl;
        return;
    }
    if (!estacao->ativo)
    {
        estacao->activate();
        std::cout << "Ponto de recarga " << id << " ativado." << std::endl;
    }
    else
    {
        std::cout << "Ponto de recarga " << id << " já estava ativo." << std::endl;
    }
}

void desativar(QuadTree &quadTree, Hash<std::string, Endereco> &estacoes, int numEnderecos, std::string id)
{
    Endereco *estacao = estacoes.search(id);
    if (estacao == nullptr)
    {
        std::cout << "Ponto de recarga " << id << " não encontrado." << std::endl;
        return;
    }
    if (estacao->ativo)
    {
        estacao->deactivate();
        std::cout << "Ponto de recarga " << id << " desativado." << std::endl;
    }
    else
    {
        std::cout << "Ponto de recarga " << id << " já estava desativado." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream genFile(argv[1]);

    int numEnderecos;

    if (std::getline(genFile, line))
    {
        std::istringstream iss(line);
        iss >> numEnderecos;
    }

    QuadTree quadTree(numEnderecos, Retangulo(Ponto(150000, 7500000), Ponto(7500000, 10000000)));
    Hash<std::string, Endereco> *estacoes = loadFile(genFile, numEnderecos, quadTree);

    std::ifstream inputFile(argv[2]);
    int numInputs;
    if (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        iss >> numInputs;
    }

    if(argv[3] != NULL && strcmp(argv[3], "lab-test") == 0){
        std::cout << "INITIALIZED" << std::endl;
    }

    while (numInputs-- && std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
        char command = line[0];
        std::istringstream iss(line.substr(1));

        if (command == 'C')
        {

            double x, y;
            int n;
            iss >> x >> y >> n;
            consultar(quadTree, *estacoes, x, y, n);
        }
        else if (command == 'A')
        {
            std::string id;
            iss >> id;
            ativar(quadTree, *estacoes, numEnderecos, id);
        }
        else if (command == 'D')
        {
            std::string id;
            iss >> id;
            desativar(quadTree, *estacoes, numEnderecos, id);
        }
    }


    if(argv[3] != NULL && strcmp(argv[3], "lab-test") == 0){
        std::cout << "FINISHED" << std::endl;
    }

    inputFile.close();
    estacoes->~Hash();
    quadTree.~QuadTree();

    return 0;
}
