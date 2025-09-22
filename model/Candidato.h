#pragma once

#include "Partido.h"
#include "Federacao.h"
#include "enums/Genero.h"
#include "enums/TipoDeputado.h"
#include <string>
#include <memory>
#include <chrono>

// Type alias for date handling using std::chrono
using Date = std::chrono::year_month_day;

/**
 * @brief Representa um candidato no sistema eleitoral
 */
class Candidato {
private:
    TipoDeputado cargo_;
    std::string numeroCandidato_;
    std::string nomeUrna_;
    std::shared_ptr<Partido> partido_;
    std::unique_ptr<Federacao> federacao_;
    Date dataNascimento_;
    Genero genero_;
    bool eleito_;
    bool votosVaoParaLegenda_;
    
    // Votos recebidos (será preenchido na leitura do arquivo de votação)
    int votosRecebidos_;

public:
    /**
     * @brief Construtor do candidato
     */
    Candidato(TipoDeputado cargo, const std::string& numeroCandidato, const std::string& nomeUrna,
              std::shared_ptr<Partido> partido, std::unique_ptr<Federacao> federacao,
              const Date& dataNascimento, Genero genero, bool eleito, bool votosVaoParaLegenda);

    // Getters
    TipoDeputado getCargo() const;
    const std::string& getNumeroCandidato() const;
    const std::string& getNomeUrna() const;
    std::shared_ptr<Partido> getPartido() const;
    const Federacao* getFederacao() const;
    const Date& getDataNascimento() const;
    Genero getGenero() const;
    bool isEleito() const;
    bool votosVaoParaLegenda() const;
    int getVotosRecebidos() const;

    // Métodos utilitários
    bool pertenceFederacao() const;
    void adicionarVotos(int votos);
    int getIdade(const Date& dataReferencia) const;

    /**
     * @brief Comparador por votos (decrescente) com critério de desempate por idade
     * Candidatos mais velhos têm prioridade em caso de empate
     */
    static bool compararPorVotosEIdade(const Candidato& c1, const Candidato& c2);

    /**
     * @brief Formata o candidato para exibição nos relatórios
     */
    std::string formatarParaRelatorio() const;

    /**
     * @brief Converte o candidato para string (para debug)
     */
    std::string toString() const;

    // Operadores de comparação
    bool operator==(const Candidato& other) const;
    bool operator!=(const Candidato& other) const;
};