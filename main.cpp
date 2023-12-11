#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Eleicao.h"
#include "LeitorDeArquivo.h"

using namespace std;

int main()
{
    Eleicao eleicao(6);
    LeitorDeArquivo leitor("candidatos.csv");
    leitor.leitura_candidatos(eleicao);

    return 0;
}