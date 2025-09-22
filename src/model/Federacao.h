#pragma once

#include <string>

/**
 * @brief Representa uma federação partidária
 */
class Federacao {
private:
    int numero_;

public:
    /**
     * @brief Construtor da federação
     * @param numero Número da federação
     */
    explicit Federacao(int numero);

    /**
     * @brief Obtém o número da federação
     * @return O número da federação
     */
    int getNumero() const;

    /**
     * @brief Verifica se a federação é válida
     * @return true se válida (número != -1), false caso contrário
     */
    bool isValida() const;

    /**
     * @brief Converte a federação para string (para debug)
     * @return String representando a federação
     */
    std::string toString() const;

    // Operadores de comparação
    bool operator==(const Federacao& other) const;
    bool operator!=(const Federacao& other) const;
};