#include "util/LeitorCandidatos.h"
#include "util/LeitorVotacao.h"
#include "util/ValidadorArgumentos.h"
#include "util/GeradorRelatorios.h"
#include "model/enums/TipoDeputado.h"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <locale>

int main(int argc, char* argv[]) {

    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale(""));

    try {
        // Converte argc/argv para vector de strings
        std::vector<std::string> args;
        for (int i = 1; i < argc; i++) {
            args.push_back(std::string(argv[i]));
        }
        
        // Valida argumentos
        ValidadorArgumentos::validar(args);
        
        // Extrai parâmetros
        TipoDeputado tipoDeputado = (args[0] == "--federal") 
            ? TipoDeputado::FEDERAL 
            : TipoDeputado::ESTADUAL;
        std::string arquivoCandidatos = args[1];
        std::string arquivoVotacao = args[2];
        Date dataEleicao = ValidadorArgumentos::parseData(args[3]);
        
        std::cout << "=== SISTEMA DE ANÁLISE ELEITORAL ===" << std::endl;
        std::cout << "Tipo: " << tipoDeputadoToString(tipoDeputado) << std::endl;
        std::cout << "Arquivo de candidatos: " << arquivoCandidatos << std::endl;
        std::cout << "Arquivo de votação: " << arquivoVotacao << std::endl;
        std::cout << "Data da eleição: " << ValidadorArgumentos::formatarData(dataEleicao) << std::endl;
        std::cout << std::endl;
        
        // Processa dados
        std::cout << "=== LENDO ARQUIVO DE CANDIDATOS ===" << std::endl;
        std::cout << "Processando arquivo: " << arquivoCandidatos << std::endl;
        std::cout << "Filtrando para: " << tipoDeputadoToString(tipoDeputado) << std::endl;
        
        auto candidatos = LeitorCandidatos::lerCandidatos(arquivoCandidatos, tipoDeputado);
        auto partidos = LeitorCandidatos::getPartidosCarregados();
        
        std::cout << "Total de candidatos válidos carregados: " << candidatos.size() << std::endl;
        std::cout << "Total de partidos encontrados: " << partidos.size() << std::endl;
        std::cout << std::endl;
        
        LeitorVotacao::lerVotacao(arquivoVotacao, candidatos, partidos, tipoDeputado);
        
        // Conta candidatos eleitos e atualiza estatísticas dos partidos
        int candidatosEleitos = 0;
        for (const auto& candidato : candidatos) {
            if (candidato->isEleito()) {
                candidatosEleitos++;
                candidato->getPartido()->incrementarCandidatosEleitos();
            }
        }
        
        std::cout << "Total de candidatos eleitos: " << candidatosEleitos << std::endl;
        std::cout << std::endl;
        
        // Gera relatórios
        std::cout << "=== RELATÓRIOS ===" << std::endl;
        std::cout << std::endl;
        
        GeradorRelatorios gerador(candidatos, partidos, dataEleicao, tipoDeputado);
        gerador.gerarTodosRelatorios();
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }
}