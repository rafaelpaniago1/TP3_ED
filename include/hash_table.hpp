#ifndef HASH_H
#define HASH_H

#include "retangulo.hpp"
#include <string>
#include <iostream>
#include "endereco.hpp"
typedef unsigned long long ull;


unsigned int hashFunction(const std::string &chave, int tamanho){

    ull hash = 0;
    ull primo = 67;
    int tamanho_chave = chave.length();

    for(int i = 0 ; i < tamanho_chave ; i++){

        hash = hash*primo + static_cast<unsigned long long>(chave[i]) * (i + 1);

    }

    return hash % tamanho;
}

template<typename c,typename v>

struct NoHash
{

    c chave;
    v valor;
    NoHash* next;
    NoHash(c c, v v) : chave(c), valor(v), next(nullptr) {}

};

template<typename c,typename v>

class Hash
{
    private:

        NoHash<c,v *> **table;
        int tamanho_tabela;
    
    public:

    Hash(int tamanho_tabela) : tamanho_tabela(tamanho_tabela)
    {
        table = new NoHash<c,v *> *[tamanho_tabela];
        for (int i = 0; i < tamanho_tabela; i++)
        {
            table[i] = nullptr;
        }
    }
    ~Hash()
    {
        for (int i = 0; i < tamanho_tabela; i++)
        {
            NoHash<c, v *> *entry = table[i];
            while (entry != nullptr)
            {
                NoHash<c, v *> *prev = entry;
                entry = entry->next;
                delete prev->value;  ///< Libera o valor apontado pelo nó.
                delete prev;  ///< Libera o nó em si.
            }
            table[i] = nullptr;
        }
        delete[] table;  ///< Libera o array de ponteiros.
    }

    void insert(const c &key, v *value)
    {
        int hashValue = hashFunction(key, tamanho_tabela);  ///< Calcula o valor de hash.
        NoHash<c, v *> *prev = nullptr;
        NoHash<c, v *> *entry = table[hashValue];

        // Percorre a lista encadeada na posição de hash até encontrar a chave ou o final da lista.
        while (entry != nullptr && entry->key != key)
        {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr)
        {
            // Se a chave não existir, cria um novo nó.
            entry = new NoHash<c, v *>(key, value);
            if (prev == nullptr)
            {
                table[hashValue] = entry;  ///< Insere o nó na tabela.
            }
            else
            {
                prev->next = entry;  ///< Insere o nó na lista encadeada.
            }
        }
        else
        {
            // Se a chave já existir, atualiza o valor.
            entry->value = value;
        }
    }

    
    v *search(const c &key)
    {
        int hashValue = hashFunction(key, tamanho_tabela);  ///< Calcula o valor de hash.
        NoHash<c, v *> *entry = table[hashValue];

        // Percorre a lista encadeada na posição de hash.
        while (entry != nullptr)
        {
            // Se encontrar a chave, retorna o valor associado.
            if (entry->key == key)
            {
                return entry->value;
            }

            entry = entry->next;  ///< Avança para o próximo nó.
        }

        return nullptr;  ///< Retorna nullptr se a chave não for encontrada.
    }
};

template class Hash<std::string, Endereco>;

#endif