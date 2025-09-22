#pragma once

#include "../model/Candidato.h"
#include "../model/Partido.h"
#include "../model/enums/TipoDeputado.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

/**
 * @brief Responsável por ler e processar o arquivo de candidatos
 */
class LeitorCandidatos {
private:
    static constexpr const char* ENCODING = "ISO-8859-1";
    static constexpr char SEPARATOR = ';';
    static constexpr const char* VOTOS_LEGENDA_MARKER = "Válido (legenda)";
    
    // Índices das colunas relevantes no CSV
    static constexpr int CD_CARGO = 13;
    static constexpr int CD_SITUACAO_CANDIDADO_TOT = 68;
    static constexpr int NR_CANDIDATO = 16;
    static constexpr int NM_URNA_CANDIDATO = 18;
    static constexpr int NR_PARTIDO = 27;
    static constexpr int SG_PARTIDO = 28;
    static constexpr int NR_FEDERACAO = 30;
    static constexpr int DT_NASCIMENTO = 42;
    static constexpr int CD_SIT_TOT_TURNO = 56;
    static constexpr int CD_GENERO = 45;
    static constexpr int NM_TIPO_DESTINACAO_VOTOS = 67;
    
    static std::map<std::string, std::shared_ptr<Partido>> partidosCache_;

public:
    /**
     * @brief Lê candidatos do arquivo CSV
     * @param arquivo Caminho para o arquivo de candidatos
     * @param tipoDesejado Tipo de deputado para filtrar
     * @return Vector com os candidatos carregados
     * @throws std::runtime_error se houver erro na leitura
     */
    static std::vector<std::unique_ptr<Candidato>> lerCandidatos(
        const std::string& arquivo, TipoDeputado tipoDesejado);

    /**
     * @brief Obtém o cache de partidos carregados
     * @return Mapa com os partidos carregados
     */
    static std::map<std::string, std::shared_ptr<Partido>> getPartidosCarregados();

private:
    /**
     * @brief Processa uma linha do arquivo CSV
     * @param linha Linha do CSV
     * @param tipoDesejado Tipo de deputado desejado
     * @param cargosCounts Mapa para contar cargos encontrados
     * @return Candidato processado ou nullptr se deve ser ignorado
     */
    static std::unique_ptr<Candidato> processarLinha(
        const std::string& linha, TipoDeputado tipoDesejado,
        std::map<int, int>& cargosCounts);

    // Métodos utilitários para parsing
    static std::string parseString(const std::string& campo);
    static int parseInt(const std::string& campo);
    static Date parseData(const std::string& campo);
    
    /**
     * @brief Remove aspas do início e fim de uma string
     * @param str String com aspas
     * @return String sem aspas
     */
    static std::string removeQuotes(const std::string& str);
    
    /**
     * @brief Divide uma string usando um delimitador
     * @param str String a ser dividida
     * @param delimiter Delimitador
     * @return Vector com as partes
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);
};