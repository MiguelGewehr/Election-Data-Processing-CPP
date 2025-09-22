#pragma once

#include <string>
#include <stdexcept>

/**
 * @brief Representa um partido político
 */
class Partido {
private:
    std::string numero_;
    std::string sigla_;
    
    // Estatísticas de votação
    int votosNominais_;
    int votosLegenda_;
    int candidatosEleitos_;

public:
    /**
     * @brief Construtor do partido
     * @param numero Número do partido
     * @param sigla Sigla do partido
     */
    Partido(const std::string& numero, const std::string& sigla);

    // Getters
    const std::string& getNumero() const;
    const std::string& getSigla() const;
    int getVotosNominais() const;
    int getVotosLegenda() const;
    int getTotalVotos() const;
    int getCandidatosEleitos() const;

    // Métodos para atualizar estatísticas
    void adicionarVotosNominais(int votos);
    void adicionarVotosLegenda(int votos);
    void incrementarCandidatosEleitos();

    /**
     * @brief Comparador por total de votos (decrescente) com critério de desempate por número do partido
     */
    static bool compararPorVotosENumero(const Partido& p1, const Partido& p2);

    /**
     * @brief Formata o partido para exibição no relatório
     */
    std::string formatarParaRelatorio(int posicao) const;

    /**
     * @brief Converte o partido para string (para debug)
     */
    std::string toString() const;

    // Operadores de comparação
    bool operator==(const Partido& other) const;
    bool operator!=(const Partido& other) const;
};