#ifndef _CANDIDATO_H_
#define _CANDIDATO_H_

#include <iostream>
#include <string>

using namespace std;

#include "Partido.h"
#include "Federacao.h"

class Candidato{
    int cargo;
    string numCandidato;
    string nomeCandidato;
    Partido partido;
    Federacao federacao;
    string dataNascimento;
    bool candidatoEleito;
    int genero;
    bool votosVaoParaLegenda;
    int numVotos;
};

#endif