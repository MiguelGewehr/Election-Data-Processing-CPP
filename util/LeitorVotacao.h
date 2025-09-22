#pragma once

#include "../model/Candidato.h"
#include "../model/Partido.h"
#include "../model/enums/TipoDeputado.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

/**
 * @brief Responsável por ler e processar o arquivo de votação
 */
class LeitorVotacao {
private:
    static constexpr const char* ENCODING = "ISO-8859-1";
    static constexpr char SEPARATOR = ';';
    
    // Índices das colunas relevantes no CSV de votação
    static constexpr int CD_CARGO = 17;
    static constexpr int NR_VOTAVEL = 19;
    static constexpr int QT_VOTOS = 21;
    
    // Números que representam votos inválidos (devem ser ignorados)
    static const std::vector<std::string> VOTOS_INVALIDOS;

public:
    /**
     * @brief Lê votação do arquivo CSV e atualiza os candidatos e partidos
     * @param arquivo Caminho para o arquivo de votação
     * @param candidatos Vector de candidatos para atualizar
     * @param partidos Mapa de partidos para atualizar
     * @param tipoDesejado Tipo de deputado para filtrar
     * @throws std::runtime_error se houver erro na leitura
     */
    static void lerVotacao(const std::string& arquivo,
                          std::vector<std::unique_ptr<Candidato>>& candidatos,
                          std::map<std::string, std::shared_ptr<Partido>>& partidos,
                          TipoDeputado tipoDesejado);

private:
    /**
     * @brief Processa uma linha do arquivo de votação
     * @param linha Linha do CSV
     * @param candidatosPorNumero Mapa de candidatos indexado por número
     * @param partidos Mapa de partidos
     * @param tipoDesejado Tipo de deputado desejado
     */
    static void processarLinhaVotacao(const std::string& linha,
                                     std::map<std::string, Candidato*>& candidatosPorNumero,
                                     std::map<std::string, std::shared_ptr<Partido>>& partidos,
                                     TipoDeputado tipoDesejado);

    /**
     * @brief Verifica se um número de votável representa voto inválido
     * @param nrVotavel Número do votável
     * @return true se for voto inválido
     */
    static bool isVotoInvalido(const std::string& nrVotavel);

    // Métodos utilitários para parsing
    static std::string parseString(const std::string& campo);
    static int parseInt(const std::string& campo);
    
    /**
     * @brief Divide uma string usando um delimitador
     * @param str String a ser dividida
     * @param delimiter Delimitador
     * @return Vector com as partes
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);
};