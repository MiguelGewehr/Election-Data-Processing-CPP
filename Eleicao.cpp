#include "Eleicao.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

Eleicao::Eleicao(int tipoDeputado) : tipoDeputado(tipoDeputado){};

int Eleicao::getTipoDeputado() const{
    return this->tipoDeputado;
}

bool Eleicao::partidoExiste(string key){
    auto it = this->partidos.find(key);
    if (it != this->partidos.end()) 
        return true;
    else 
        return false;      
}

Partido* Eleicao::getPartido(string key){
    auto it = this->partidos.find(key);
    return (it->second);
}

void Eleicao::addPartido(Partido *p){
    this->partidos.insert({p->getNumPartido(),p});
}

void Eleicao::addCandidatoEleito(Candidato *c){
    this->candidatosEleitos.insert({c->getNumCandidato(), c});
}

void Eleicao::addCandidato(Candidato *c){
    this->candidatos.insert({c->getNumCandidato(), c});
}

int Eleicao::getNumCandidatosEleitos(){
    return this->candidatosEleitos.size();
}

bool Eleicao::candidatoExiste(string key){
    auto it = this->candidatos.find(key);
    if (it != this->candidatos.end()) 
        return true;
    else 
        return false;
}

Candidato* Eleicao::getCandidato(string key){
    auto it = this->candidatos.find(key);
    return it->second;
}

void Eleicao::somaVotosLegenda(int numVotos){
    this->numVotosLegenda += numVotos;
}

std::string removerAspas(const std::string &str)
{
    std::string novaString = str;

    // Procurar as aspas e removê-las
    size_t pos = novaString.find('"');
    while (pos != std::string::npos)
    {
        novaString.erase(pos, 1);        // Remove uma aspa na posição encontrada
        pos = novaString.find('"', pos); // Procura a próxima aspa a partir da posição atual
    }

    return novaString;
}

void leLixo(istringstream &linhaStream, int n){
    string lixo;
    for(int i = 0; i < n; i++)
        getline(linhaStream, lixo, ';');
}

void leitura_candidatos(Eleicao &eleicao, char path[])
{

    ifstream inputStream(path);
    string linha;
    getline(inputStream, linha); // cabeçalho
    
    while (getline(inputStream, linha))
    {
        istringstream linhaStream(linha);
        string aux;

        leLixo(linhaStream, 13);

        getline(linhaStream, aux, ';');
        aux = removerAspas(aux);

        int cargo = stoi(aux); // 6- deputado federal e 7-estadual

        leLixo(linhaStream, 2);

        getline(linhaStream, aux, ';');
        string numCandidato = removerAspas(aux);
        leLixo(linhaStream, 1);
        getline(linhaStream, aux, ';');

        string nomeCandidato = removerAspas(aux);

        leLixo(linhaStream, 8);

        getline(linhaStream, aux, ';');
        string numPartido = removerAspas(aux);
        getline(linhaStream, aux, ';');
        string siglaPartido = removerAspas(aux);

        leLixo(linhaStream, 1);
        getline(linhaStream, aux, ';');
        int numFederacao = stoi(removerAspas(aux)); // numero da fereacao (-1 = sem federacao)

        leLixo(linhaStream, 11);
        
        getline(linhaStream, aux, ';');
        string dataNascimento = aux;

        leLixo(linhaStream, 2);
        
        getline(linhaStream, aux, ';');
        int genero = stoi(removerAspas(aux)); // 2-masculino e 4-feminino

        leLixo(linhaStream, 10);

        getline(linhaStream, aux, ';');
        int sit_eleito = stoi(removerAspas(aux));

        bool candidatoEleito;

        if(sit_eleito == 2 || sit_eleito == 3)
            candidatoEleito = true;
        else
            candidatoEleito = false;

        leLixo(linhaStream, 10);

        getline(linhaStream, aux, ';');
        string destinacao_votos = removerAspas(aux); // se for valido(legenda) entra para a contagem de legenda

        bool votosVaoParaLegenda;

        if(destinacao_votos == "Válido (legenda)")
            votosVaoParaLegenda = true;
        else
            votosVaoParaLegenda = false;

        getline(linhaStream, aux, ';');
        string situacaoCandidato = removerAspas(aux); // 2 ou 16 são contabilizados

        bool existePartido = eleicao.partidoExiste(numPartido);

        Partido *partido;

        if(!existePartido){
            partido = new Partido(numPartido, siglaPartido);
            eleicao.addPartido(partido);
        }
        else{ 
            partido = eleicao.getPartido(numPartido);
        }
        
        if (situacaoCandidato == "2" || situacaoCandidato == "16" || votosVaoParaLegenda){

            Federacao federacao(numFederacao);

            Candidato *candidato = new Candidato(cargo, numCandidato, nomeCandidato, partido, federacao, dataNascimento, genero, votosVaoParaLegenda, candidatoEleito);

            if(candidatoEleito && cargo == eleicao.getTipoDeputado()){
                eleicao.addCandidatoEleito(candidato);
                candidato->getPartido().incrementaNumCandidatosEleitos();
            }

            eleicao.addCandidato(candidato);
        }
    }
    inputStream.close();
}

void leitura_votacao(Eleicao &eleicao, char path[])
{

    ifstream inputStream(path);
    string linha;
    getline(inputStream, linha); // cabeçalho
    int i=0;

    while (getline(inputStream, linha))
    {
        istringstream linhaStream(linha);
        string aux;

        leLixo(linhaStream, 17);
        
        getline(linhaStream, aux, ';');
        aux = removerAspas(aux);

        int cargo = stoi(aux); // 6- deputado federal e 7-estadual

        leLixo(linhaStream, 1);

        getline(linhaStream, aux, ';');
        string nrVotavel = removerAspas(aux);

        if (cargo == eleicao.getTipoDeputado() && !(nrVotavel == "95" || nrVotavel == "96" || nrVotavel == "97" || nrVotavel == "98"))
        {
            i++;
            leLixo(linhaStream, 1);
            
            getline(linhaStream, aux, ';');

            aux = removerAspas(aux);

            
            int numVotos = stoi(aux);


            if(eleicao.candidatoExiste(nrVotavel)){

                Candidato *c = eleicao.getCandidato(nrVotavel);
                
                Partido p = c->getPartido();

                if(c->getVotosVaoParaLegenda()){
                    p.somaVotosLegenda(numVotos);
                    eleicao.somaVotosLegenda(numVotos);
                }
                else{
                    c->somaVotos(numVotos);
                }
            }    
                if(eleicao.partidoExiste(nrVotavel)){
                    Partido *p = eleicao.getPartido(nrVotavel);
                    p->somaVotosLegenda(numVotos);
                    eleicao.somaVotosLegenda(numVotos);
                }
        }
        
    }
        printf("%d %d\n",i, eleicao.getTipoDeputado());
}

void gerarRelatorio(Eleicao &eleicao){
    
    printf("Número de vagas: %d\n\n", eleicao.getNumCandidatosEleitos());
}