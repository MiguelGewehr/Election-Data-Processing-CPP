#include "Candidato.h"
#include "Partido.h"

Candidato::Candidato(int cargo, string numCandidato, string nomeCandidato, Partido *partido, Federacao federacao, string dataNascimento, int genero, bool votosVaoParaLegenda, bool candidatoEleito) : cargo(cargo), numCandidato(numCandidato), nomeCandidato(nomeCandidato), partido(partido), federacao(federacao), dataNascimento(dataNascimento), genero(genero), votosVaoParaLegenda(votosVaoParaLegenda), candidatoEleito(candidatoEleito){}

string Candidato::getNumCandidato() const{
    return this->numCandidato;
}

Partido Candidato::getPartido(){
    return *(this->partido);
}

bool Candidato::getVotosVaoParaLegenda() const{
    return this->votosVaoParaLegenda;
}

void Candidato::somaVotos(int numVotos){
    this->numVotos += numVotos;
}

int Candidato::getNumVotos() const{
    return this->numVotos;
}

string Candidato::getNome() const{
    return this->nomeCandidato;
}

int Candidato::getCargo() const{
    return this->cargo;
}

bool Candidato::getCandidatoEleito() const{
    return this->candidatoEleito;
}