#include "LeitorDeArquivo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Eleicao.h"

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

LeitorDeArquivo::LeitorDeArquivo(string caminho)
{
    this->nome_arquivo_canidatos = caminho;
    this->nome_arquivo_votos = caminho;
}

void LeitorDeArquivo::leitura_candidatos(Eleicao eleicao)
{

    ifstream inputStream("candidatos.csv");
    string linha;
    getline(inputStream, linha); // cabeçalho
    cout << linha << endl;

    while (getline(inputStream, linha))
    {
        istringstream linhaStream(linha);
        string lixo;
        string aux;

        for (int i = 0; i < 13; i++)
        {
            getline(linhaStream, lixo, ';');
        }

        getline(linhaStream, aux, ';');
        aux = removerAspas(aux);

        int cargo = stoi(aux); // 6- deputado federal e 7-estadual

        for (int i = 0; i < 2; i++)
        {
            getline(linhaStream, lixo, ';');
        }

        getline(linhaStream, aux, ';');
        int nr_candidato = stoi(removerAspas(aux));
        getline(linhaStream, lixo, ';');
        getline(linhaStream, aux, ';');

        string nm_urna_candidato = removerAspas(aux);

        for (int i = 0; i < 8; i++)
        {
            getline(linhaStream, lixo, ';');
        }

        getline(linhaStream, aux, ';');
        int nr_partido = stoi(removerAspas(aux));
        getline(linhaStream, aux, ';');
        string sg_partido = removerAspas(aux);

        getline(linhaStream, lixo, ';');
        getline(linhaStream, aux, ';');
        int nr_federacao = stoi(removerAspas(aux)); // numero da fereacao (-1 = sem federacao)

        for (int i = 0; i < 11; i++)
        {
            getline(linhaStream, lixo, ';');
        }
        getline(linhaStream, aux, ';');
        string data_nascimento = aux;

        for (int i = 0; i < 2; i++)
        {
            getline(linhaStream, lixo, ';');
        }
        getline(linhaStream, aux, ';');
        int cd_genero = stoi(removerAspas(aux)); // 2-masculino e 4-feminino

        for (int i = 0; i < 10; i++)
        {
            getline(linhaStream, lixo, ';');
        }

        getline(linhaStream, aux, ';');
        int sit_eleito = stoi(removerAspas(aux));

        for (int i = 0; i < 10; i++)
        {
            getline(linhaStream, lixo, ';');
        }

        getline(linhaStream, aux, ';');
        string destinacao_votos = removerAspas(aux); // se for valido(legenda) entra para a contagem de legenda

        getline(linhaStream, aux, ';');
        string cd_situacao_candidato_tot = removerAspas(aux); // 2 ou 16 são contabilizados

        cout << cd_situacao_candidato_tot << endl;

        // cout << sit_eleito << endl;
    }
    inputStream.close();
}
