#ifndef _CANDIDATO_H_
#define _CANDIDATO_H_

#include <iostream>
#include <string>

using namespace std;

class Partido;
#include "Federacao.h"

class Candidato
{
    int cargo;
    string numCandidato;
    string nomeCandidato;
    Partido *partido;
    Federacao federacao;
    string dataNascimento;
    bool candidatoEleito;
    int genero;
    bool votosVaoParaLegenda;
    int numVotos;

public:
    Candidato(int cargo, string numCandidato, string nomeCandidato, Partido *partido, Federacao federacao, string dataNascimento, int genero, bool votosVaoParaLegenda, bool candidatoEleito);
    void somaVotos(int numVotos);
    int getCargo();
    string getNumCandidato() const;
    string getNomeCandidato();
    Partido getPartido();
    Federacao getFederacao();
    string getDataNascimento();
    bool getCandidatoEleito();
    int getGenero();
    bool getVotosVaoParaLegenda();
    int getNumVotos() ;
};

#endif