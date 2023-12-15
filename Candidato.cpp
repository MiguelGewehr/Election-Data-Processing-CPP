#include "Candidato.h"
#include "Partido.h"

Candidato::Candidato(int cargo, string numCandidato, string nomeCandidato, Partido *partido, Federacao federacao, string dataNascimento, int genero, bool votosVaoParaLegenda, bool candidatoEleito) : cargo(cargo), numCandidato(numCandidato), nomeCandidato(nomeCandidato), partido(partido), federacao(federacao), dataNascimento(dataNascimento), genero(genero), votosVaoParaLegenda(votosVaoParaLegenda), candidatoEleito(candidatoEleito){}

