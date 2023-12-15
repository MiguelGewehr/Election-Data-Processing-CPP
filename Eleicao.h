#ifndef _ELEICAO_H_
#define _ELEICAO_H_
#include <map>
#include <string>
#include "Candidato.h"

using namespace std;

class Eleicao
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
    Eleicao(int tipoDeputado);
    int getNumVotosTotais();
    int getTipoDeputado() const;
    int getNumVotosLegenda();
    void addCandidato(Candidato c);
    void addCandidatoEleito(Candidato c);
    int getNumVotosNominais();
    void addPartido(Partido p);
    void printaCandidatos();
    int getNumCandidatosEleitos();
};

void leitura_candidatos(Eleicao eleicao, char path[]);
void leitura_votacao(Eleicao eleicao, char path[]);

#endif