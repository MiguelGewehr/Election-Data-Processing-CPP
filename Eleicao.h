#ifndef _ELEICAO_H_
#define _ELEICAO_H_
#include <map>
#include <string>
#include <Candidato.h>

using namespace std;

class
{
private:
    std::map<string, Candidato> candidatos;
    std::map<string, Candidato> candidatosEleitos;
    std::map<string, Partido> partidos;
    int tipoDeputado;
    int numVotosNominais;
    int numVotosLegenda;
    int numVotosTotais;

public:
    int getNumVotosTotais();
    int getTipoDeputado();
    int getNumVotosLegenda();
    void addCandidato(Candidato c);
    void addCandidatoEleito(Candidato c);
    int getNumVotosNominais();
    void addPartido(Partido p);
    void printaCandidatos();
    int getNumCandidatosEleitos();
};

#endif