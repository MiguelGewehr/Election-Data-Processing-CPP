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
    string getSiglaPartido();
    void somaVotosNominal(int numVotos);
    int getNumCandidatosEleitos() const;
    int getVotosNominal() const;
    int getNumVotos() const;
    int getVotosLegenda();
    /*void somaVotos();
    Candidato getCandidatoMenosVotado();
    void setCandidatoMenosVotado(Candidato candidatoMenosVotado);
    */
};

#endif