#ifndef _PARTIDO_H_
#define _PARTIDO_H_

class Partido
{
    string numPartido;
    string siglaPartido;
    int numVotos;
    int numVotosLegenda;
    int numVotosNominal;
    int numCandidatosEleitos;
    Candidato candidatoMenosVotado;

public:
    void somaVotos();
    string getNumPartido();
    string getSiglaPartido();
    int getNumVotos();
    Candidato getCandidatoMenosVotado();
    void setCandidatoMenosVotado(Candidato candidatoMenosVotado);
    int getVotosLegenda();
    int getVotosNominal();
    void somaVotosLegenda(int numVotos);
    void somaVotosNominal(int numVotos);
    int getNumCandidatosEleitos();
    void incrementaNumCandidatosEleitos();
};

#endif