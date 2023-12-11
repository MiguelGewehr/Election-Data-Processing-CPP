#ifndef _LEITORDEARQUIVO_H_
#define _LEITORDEARQUIVO_H_
#include <string>
#include "Eleicao.h"

using namespace std;

class LeitorDeArquivo
{
private:
    string nome_arquivo_canidatos;
    string nome_arquivo_votos;

public:
    LeitorDeArquivo(string caminho);
    void LeitorDeArquivo:: leitura_candidatos(Eleicao eleicao);
    ~LeitorDeArquivo();
};



LeitorDeArquivo::~LeitorDeArquivo()
{
}

#endif
