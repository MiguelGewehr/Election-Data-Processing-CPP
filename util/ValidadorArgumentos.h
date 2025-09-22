#pragma once

#include "../model/Candidato.h"
#include <vector>
#include <string>

/**
 * @brief Valida argumentos da linha de comando
 */
class ValidadorArgumentos {
public:
    /**
     * @brief Valida todos os argumentos fornecidos
     * @param args Vetor de argumentos da linha de comando
     * @throws std::invalid_argument se algum argumento for inválido
     */
    static void validar(const std::vector<std::string>& args);

    /**
     * @brief Converte string de data para objeto Date
     * @param data String no formato dd/mm/yyyy
     * @return Objeto Date correspondente
     * @throws std::invalid_argument se a data for inválida
     */
    static Date parseData(const std::string& data);

    /**
     * @brief Formata objeto Date para string
     * @param data Objeto Date
     * @return String no formato dd/mm/yyyy
     */
    static std::string formatarData(const Date& data);

private:
    /**
     * @brief Valida o tipo de deputado
     * @param tipo String do tipo (--federal ou --estadual)
     * @throws std::invalid_argument se o tipo for inválido
     */
    static void validarTipoDeputado(const std::string& tipo);

    /**
     * @brief Valida se um arquivo existe e é legível
     * @param caminho Caminho para o arquivo
     * @param tipo Tipo do arquivo (para mensagens de erro)
     * @throws std::invalid_argument se o arquivo for inválido
     */
    static void validarArquivo(const std::string& caminho, const std::string& tipo);

    /**
     * @brief Valida formato da data
     * @param data String da data
     * @throws std::invalid_argument se a data for inválida
     */
    static void validarData(const std::string& data);

    /**
     * @brief Mostra instruções de uso do programa
     */
    static void mostrarUso();
};