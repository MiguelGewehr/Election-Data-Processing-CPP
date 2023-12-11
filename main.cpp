#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

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

int main()
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

        int cargo = stoi(aux);

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

        /*string nomeFuncionario;
        getline(linhaStream, nomeFuncionario, ';');
        string codigoDepStr;
        getline(linhaStream, codigoDepStr, ';');
        int codigoDep = stoi(codigoDepStr);
        // inv: tenho dados para criar funcionario
        e.findDepartamento(codigoDep).createFuncionario(codigoFun, nomeFuncionario);
        */
        cout << nm_urna_candidato << endl;
    }
    inputStream.close();

    return 0;
}