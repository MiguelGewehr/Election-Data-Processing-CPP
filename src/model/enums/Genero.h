#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Enumera os gêneros dos candidatos
 */
enum class Genero {
    MASCULINO = 2,
    FEMININO = 4
};

/**
 * @brief Converte código numérico para Genero
 * @param codigo O código do gênero (2 para masculino, 4 para feminino)
 * @return O enum Genero correspondente
 * @throws std::invalid_argument se o código não for válido
 */
inline Genero generoFromCodigo(int codigo) {
    switch (codigo) {
        case 2: return Genero::MASCULINO;
        case 4: return Genero::FEMININO;
        default:
            throw std::invalid_argument("Código de gênero inválido: " + std::to_string(codigo));
    }
}

/**
 * @brief Converte Genero para string
 * @param genero O enum Genero
 * @return String representando o gênero
 */
inline std::string generoToString(Genero genero) {
    switch (genero) {
        case Genero::MASCULINO: return "Masculino";
        case Genero::FEMININO: return "Feminino";
        default: return "Desconhecido";
    }
}

/**
 * @brief Obtém o código numérico do gênero
 * @param genero O enum Genero
 * @return O código numérico correspondente
 */
inline int getCodigoGenero(Genero genero) {
    return static_cast<int>(genero);
}