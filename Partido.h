#ifndef _PARTIDO_H_
#define _PARTIDO_H_
#include "Candidato.h"

class Partido
{
    string numPartido;
    string siglaPartido;
    int numVotos=0;
    int numVotosLegenda=0;
    int numVotosNominal=0;
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
    void somaVotos();
    int getVotosLegenda() const;
    /*Candidato getCandidatoMenosVotado();
    void setCandidatoMenosVotado(Candidato candidatoMenosVotado);
    */
};

#endif