#ifndef _ELEICAO_H_
#define _ELEICAO_H_
#include <map>
#include <string>
#include "Candidato.h"
#include "Partido.h"
#include <vector>

using namespace std;

class Eleicao
{
private:
    std::map<string, Candidato*> candidatos;
    std::map<string, Candidato*> candidatosEleitos;
    std::map<string, Partido*> partidos;
    int tipoDeputado;
    int numVotosNominais=0;
    int numVotosLegenda=0;
    int numVotosTotais=0;

public:
    Eleicao(int tipoDeputado);
    int getNumVotosTotais() const;
    int getTipoDeputado() const;
    int getNumVotosLegenda() const;
    void addCandidato(Candidato *c);
    void addCandidatoEleito(Candidato *c);
    int getNumVotosNominais() const;
    void addPartido(Partido *p);
    void printaCandidatos();
    int getNumCandidatosEleitos();
    bool partidoExiste(string key);
    Partido* getPartido(string key);
    bool candidatoExiste(string key);
    Candidato* getCandidato(string key);
    void somaVotosLegenda(int numVotos);
    vector<Candidato*> ordenaCandidatosEleitosPorVoto();
    vector<Candidato*> ordenaCandidatosPorVoto(int tipoDeputado);
    void calculaVotosNominais(vector<Candidato*> &candidatos);
    vector<Partido*> ordenaVotosPartidos();
    void calculaPorcentagemGenero(vector<Candidato*> candidatosEleitos);
    void relatorioDez(Eleicao eleicao);
    void somaVotosTotais();
};

void leitura_candidatos(Eleicao &eleicao, char path[]);
void leitura_votacao(Eleicao &eleicao, char path[]);
void gerarRelatorio(Eleicao &eleicao, int tipoDeputado);
vector<Candidato*> relatorioDois(Eleicao &eleicao);
vector<Candidato*> relatorioTresEQuatro(Eleicao &eleicao, int TipoDeputado);
void relatorioCinco(Eleicao eleicao, vector<Candidato*> candidatosEleitosOrdenados, vector<Candidato*> candidatosOrdenados);
void relatorioSeis(Eleicao &eleicao, vector<Candidato*> candidatos);
void relatorioNove(Eleicao eleicao, vector<Candidato*> candidatosEleitos);
void relatorioDez(Eleicao eleicao);

#endif