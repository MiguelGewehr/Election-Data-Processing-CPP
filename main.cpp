#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string.h>
#include "Eleicao.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 5){
        printf("Erro ao ler os argumentos\n");
        exit(1);
    }
    
    int tipoDeputado = 0;
    
    if(strcmp(argv[1],"--estadual") == 0)
        tipoDeputado = 7;
    else
        tipoDeputado = 6;
    
    Eleicao eleicao(tipoDeputado);

    
    leitura_candidatos(eleicao, argv[2]);

    leitura_votacao(eleicao, argv[3]);

    return 0;
}