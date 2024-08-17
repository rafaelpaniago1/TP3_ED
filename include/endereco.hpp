#ifndef ENDERECO_H
#define ENDERECO_H

#include <retangulo.hpp>
#include <string>
#include <ostream>

struct Endereco{

    Ponto* ponto;
    std::string idend;
    long id_logrado;
    std::string sigla_tipo;
    std::string nome_logra;
    std::string numero_imo;
    std::string nome_bairr;
    std::string nome_regio;
    int cep;
    bool ativo = true;

    Endereco() = default;

    Endereco(Ponto &ponto, const std::string &idend, long id_logrado, const std::string &sigla_tipo,
            const std::string &nome_logra, const std::string &numero_imo, const std::string &nome_bairr,
            const std::string &nome_regio, int cep)
    : ponto(&ponto), idend(idend), id_logrado(id_logrado), sigla_tipo(sigla_tipo), nome_logra(nome_logra),
        numero_imo(numero_imo), nome_bairr(nome_bairr), nome_regio(nome_regio), cep(cep) {}
    void activate()
    {
        ativo = true;
        ponto->activate();
    }
    void deactivate()
    {
        ativo = false;
        ponto->deactivate();
    }
};

std::ostream &operator<<(std::ostream &os, const Endereco &address)
{
    os << address.sigla_tipo << " " << address.nome_logra << ", "
       << address.numero_imo << ", " << address.nome_bairr << ", "
       << address.nome_regio << ", " << address.cep;
    return os;
}

#endif