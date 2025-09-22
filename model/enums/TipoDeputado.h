#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Enumera os tipos de deputado
 */
enum class TipoDeputado {
    FEDERAL = 6,
    ESTADUAL = 7
};

/**
 * @brief Converte código numérico para TipoDeputado
 * @param codigo O código do tipo (6 para federal, 7 para estadual)
 * @return O enum TipoDeputado correspondente
 * @throws std::invalid_argument se o código não for válido
 */
inline TipoDeputado tipoDeputadoFromCodigo(int codigo) {
    switch (codigo) {
        case 6: return TipoDeputado::FEDERAL;
        case 7: return TipoDeputado::ESTADUAL;
        default:
            throw std::invalid_argument("Código de cargo inválido: " + std::to_string(codigo));
    }
}

/**
 * @brief Converte TipoDeputado para string
 * @param tipo O enum TipoDeputado
 * @return String representando o tipo de deputado
 */
inline std::string tipoDeputadoToString(TipoDeputado tipo) {
    switch (tipo) {
        case TipoDeputado::FEDERAL: return "Deputado Federal";
        case TipoDeputado::ESTADUAL: return "Deputado Estadual";
        default: return "Desconhecido";
    }
}

/**
 * @brief Obtém o código numérico do tipo de deputado
 * @param tipo O enum TipoDeputado
 * @return O código numérico correspondente
 */
inline int getCodigoTipoDeputado(TipoDeputado tipo) {
    return static_cast<int>(tipo);
}

/**
 * @brief Obtém o nome do cargo baseado no código
 * @param codigo O código do cargo
 * @return String com o nome do cargo
 */
inline std::string getNomeCargo(int codigo) {
    switch (codigo) {
        case 3: return "Senador";
        case 4: return "Governador"; 
        case 5: return "Presidente";
        case 6: return "Deputado Federal";
        case 7: return "Deputado Estadual";
        case 9: return "Vice-governador";
        case 10: return "Vice-presidente";
        default: return "Desconhecido";
    }
}