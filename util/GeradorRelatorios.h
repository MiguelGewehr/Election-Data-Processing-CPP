#pragma once

#include "../model/Candidato.h"
#include "../model/Partido.h"
#include "../model/enums/TipoDeputado.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

/**
 * @brief Responsável por gerar todos os relatórios do sistema eleitoral
 */
class GeradorRelatorios {
private:
    std::vector<std::unique_ptr<Candidato>>& candidatos_;
    std::map<std::string, std::shared_ptr<Partido>>& partidos_;
    Date dataEleicao_;
    TipoDeputado tipoDeputado_;
    int numeroVagas_;

public:
    /**
     * @brief Construtor do gerador de relatórios
     */
    GeradorRelatorios(std::vector<std::unique_ptr<Candidato>>& candidatos,
                     std::map<std::string, std::shared_ptr<Partido>>& partidos,
                     const Date& dataEleicao,
                     TipoDeputado tipoDeputado);

    /**
     * @brief Gera todos os relatórios
     */
    void gerarTodosRelatorios();

private:
    // Métodos para cada relatório
    void relatorio1NumeroVagas();
    void relatorio2CandidatosEleitos();
    void relatorio3CandidatosMaisVotados();
    void relatorio4TeriamSidoEleitos();
    void relatorio5BeneficiadosSistemaProporcional();
    void relatorio6VotacaoPartidos();
    void relatorio7PrimeiroUltimoColocados();
    void relatorio8DistribuicaoIdade();
    void relatorio9DistribuicaoGenero();
    void relatorio10TotalVotos();

    // Métodos auxiliares para cálculos
    int calcularTotalVotos() const;
    int calcularVotosNominais() const;
    int calcularVotosLegenda() const;
    double calcularPercentualNominais() const;
    double calcularPercentualLegenda() const;
    
    /**
     * @brief Obtém número do partido baseado na sigla
     * @param sigla Sigla do partido
     * @return Número do partido
     */
    std::string getNumeroPartido(const std::string& sigla) const;
    
    /**
     * @brief Formata número com separadores de milhares
     * @param numero Número a ser formatado
     * @return String formatada
     */
    std::string formatarNumero(int numero) const;
};