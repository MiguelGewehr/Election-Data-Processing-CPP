#ifndef _PARTIDO_H_
#define _PARTIDO_H_
#include "Candidato.h"

class Partido
{
    string numPartido;
    string siglaPartido;
    int numVotos;
    int numVotosLegenda;
    int numVotosNominal;
    int numCandidatosEleitos=0;
   // Candidato candidatoMenosVotado;

public:
    Partido(string numPartido, string siglaPartido);
    string getNumPartido() const;
    void incrementaNumCandidatosEleitos();
    void somaVotosLegenda(int numVotos);
    /*void somaVotos();
    string getSiglaPartido();
    int getNumVotos();
    Candidato getCandidatoMenosVotado();
    void setCandidatoMenosVotado(Candidato candidatoMenosVotado);
    int getVotosLegenda();
    int getVotosNominal();
    void somaVotosNominal(int numVotos);
    int getNumCandidatosEleitos();
    */
};

#endif