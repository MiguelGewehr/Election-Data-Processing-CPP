#include "Partido.h"

Partido::Partido(string numPartido, string siglaPartido) : numPartido(numPartido), siglaPartido(siglaPartido){}

string Partido::getNumPartido() const{
    return this->numPartido;
}

void Partido::incrementaNumCandidatosEleitos(){
    this->numCandidatosEleitos++;
}

void Partido::somaVotosLegenda(int numVotos){
    this->numVotosLegenda += numVotos;
}

string Partido::getSiglaPartido(){
    return this->siglaPartido;
}

void Partido::somaVotosNominal(int numVotos){
    this->numVotosNominal += numVotos;
}

int Partido::getNumCandidatosEleitos() const{
    return this->numCandidatosEleitos;
}

int Partido::getVotosNominal() const{
    return this->numVotosNominal;
}

int Partido::getNumVotos() const{
    return this->numVotos;
}

int Partido::getVotosLegenda(){
    return this->numVotosLegenda;
}