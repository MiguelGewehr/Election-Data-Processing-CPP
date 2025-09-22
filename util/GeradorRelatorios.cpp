#include "GeradorRelatorios.h"
#include "../model/enums/Genero.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <locale>
#include <unordered_set>

GeradorRelatorios::GeradorRelatorios(std::vector<std::unique_ptr<Candidato>>& candidatos,
                                   std::map<std::string, std::shared_ptr<Partido>>& partidos,
                                   const Date& dataEleicao,
                                   TipoDeputado tipoDeputado)
    : candidatos_(candidatos), partidos_(partidos), dataEleicao_(dataEleicao), 
      tipoDeputado_(tipoDeputado) {
    
    // Conta número de vagas (candidatos eleitos)
    numeroVagas_ = 0;
    for (const auto& candidato : candidatos_) {
        if (candidato->isEleito()) {
            numeroVagas_++;
        }
    }
}

void GeradorRelatorios::gerarTodosRelatorios() {
    relatorio1NumeroVagas();
    relatorio2CandidatosEleitos();
    relatorio3CandidatosMaisVotados();
    relatorio4TeriamSidoEleitos();
    relatorio5BeneficiadosSistemaProporcional();
    relatorio6VotacaoPartidos();
    relatorio7PrimeiroUltimoColocados();
    relatorio8DistribuicaoIdade();
    relatorio9DistribuicaoGenero();
    relatorio10TotalVotos();
}

void GeradorRelatorios::relatorio1NumeroVagas() {
    std::cout << "Número de vagas: " << numeroVagas_ << std::endl;
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio2CandidatosEleitos() {
    std::string tipoTexto = (tipoDeputado_ == TipoDeputado::FEDERAL) ? "federais" : "estaduais";
    std::cout << "Deputados " << tipoTexto << " eleitos:" << std::endl;
    
    std::vector<Candidato*> eleitos;
    for (const auto& candidato : candidatos_) {
        if (candidato->isEleito()) {
            eleitos.push_back(candidato.get());
        }
    }
    
    std::sort(eleitos.begin(), eleitos.end(), 
              [](const Candidato* a, const Candidato* b) {
                  return Candidato::compararPorVotosEIdade(*a, *b);
              });
    
    for (size_t i = 0; i < eleitos.size(); i++) {
        const auto& candidato = eleitos[i];
        std::string prefixoFederacao = candidato->pertenceFederacao() ? "*" : "";
        std::cout << (i + 1) << " - " << prefixoFederacao << candidato->getNomeUrna() 
                  << " (" << candidato->getPartido()->getSigla() << ", " 
                  << formatarNumero(candidato->getVotosRecebidos()) << " votos)" << std::endl;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio3CandidatosMaisVotados() {
    std::cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;
    
    std::vector<Candidato*> todosCandidatos;
    for (const auto& candidato : candidatos_) {
        todosCandidatos.push_back(candidato.get());
    }
    
    std::sort(todosCandidatos.begin(), todosCandidatos.end(),
              [](const Candidato* a, const Candidato* b) {
                  return Candidato::compararPorVotosEIdade(*a, *b);
              });
    
    int limite = std::min(static_cast<int>(todosCandidatos.size()), numeroVagas_);
    for (int i = 0; i < limite; i++) {
        const auto& candidato = todosCandidatos[i];
        std::string prefixoFederacao = candidato->pertenceFederacao() ? "*" : "";
        std::cout << (i + 1) << " - " << prefixoFederacao << candidato->getNomeUrna() 
                  << " (" << candidato->getPartido()->getSigla() << ", " 
                  << formatarNumero(candidato->getVotosRecebidos()) << " votos)" << std::endl;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio4TeriamSidoEleitos() {
    std::cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << std::endl;
    std::cout << "(com sua posição no ranking de mais votados)" << std::endl;
    
    std::vector<Candidato*> todosCandidatos;
    std::unordered_set<std::string> eleitosSet;
    
    for (const auto& candidato : candidatos_) {
        todosCandidatos.push_back(candidato.get());
        if (candidato->isEleito()) {
            eleitosSet.insert(candidato->getNumeroCandidato());
        }
    }
    
    std::sort(todosCandidatos.begin(), todosCandidatos.end(),
              [](const Candidato* a, const Candidato* b) {
                  return Candidato::compararPorVotosEIdade(*a, *b);
              });
    
    int encontrados = 0;
    for (int i = 0; i < numeroVagas_ && i < static_cast<int>(todosCandidatos.size()); i++) {
        const auto& candidato = todosCandidatos[i];
        if (eleitosSet.find(candidato->getNumeroCandidato()) == eleitosSet.end()) {
            std::string prefixoFederacao = candidato->pertenceFederacao() ? "*" : "";
            std::cout << (i + 1) << " - " << prefixoFederacao << candidato->getNomeUrna() 
                      << " (" << candidato->getPartido()->getSigla() << ", " 
                      << formatarNumero(candidato->getVotosRecebidos()) << " votos)" << std::endl;
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        std::cout << "Nenhum candidato nesta situação." << std::endl;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio5BeneficiadosSistemaProporcional() {
    std::cout << "Eleitos, que se beneficiaram do sistema proporcional:" << std::endl;
    std::cout << "(com sua posição no ranking de mais votados)" << std::endl;
    
    std::vector<Candidato*> todosCandidatos;
    std::unordered_set<std::string> eleitosSet;
    
    for (const auto& candidato : candidatos_) {
        todosCandidatos.push_back(candidato.get());
        if (candidato->isEleito()) {
            eleitosSet.insert(candidato->getNumeroCandidato());
        }
    }
    
    std::sort(todosCandidatos.begin(), todosCandidatos.end(),
              [](const Candidato* a, const Candidato* b) {
                  return Candidato::compararPorVotosEIdade(*a, *b);
              });
    
    std::vector<std::string> beneficiados;
    
    for (size_t i = 0; i < todosCandidatos.size(); i++) {
        const auto& candidato = todosCandidatos[i];
        int posicao = i + 1;
        
        if (posicao > numeroVagas_ && eleitosSet.find(candidato->getNumeroCandidato()) != eleitosSet.end()) {
            std::string prefixoFederacao = candidato->pertenceFederacao() ? "*" : "";
            std::ostringstream oss;
            oss << posicao << " - " << prefixoFederacao << candidato->getNomeUrna() 
                << " (" << candidato->getPartido()->getSigla() << ", " 
                << formatarNumero(candidato->getVotosRecebidos()) << " votos)";
            beneficiados.push_back(oss.str());
        }
    }
    
    for (const auto& linha : beneficiados) {
        std::cout << linha << std::endl;
    }
    
    if (beneficiados.empty()) {
        std::cout << "Nenhum candidato nesta situação." << std::endl;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio6VotacaoPartidos() {
    std::cout << "Votação dos partidos e número de candidatos eleitos:" << std::endl;
    
    // Conta candidatos eleitos e votos nominais por partido
    std::map<std::string, int> eleitosPorPartido;
    std::map<std::string, int> votosNominaisPorPartido;
    
    for (const auto& candidato : candidatos_) {
        std::string sigla = candidato->getPartido()->getSigla();
        
        if (candidato->isEleito()) {
            eleitosPorPartido[sigla]++;
        }
        
        if (!candidato->votosVaoParaLegenda()) {
            votosNominaisPorPartido[sigla] += candidato->getVotosRecebidos();
        }
    }
    
    std::vector<std::shared_ptr<Partido>> partidosOrdenados;
    for (const auto& par : partidos_) {
        partidosOrdenados.push_back(par.second);
    }
    
    std::sort(partidosOrdenados.begin(), partidosOrdenados.end(),
              [](const std::shared_ptr<Partido>& a, const std::shared_ptr<Partido>& b) {
                  return Partido::compararPorVotosENumero(*a, *b);
              });
    
    for (size_t i = 0; i < partidosOrdenados.size(); i++) {
        const auto& partido = partidosOrdenados[i];
        int eleitos = eleitosPorPartido[partido->getSigla()];
        int nominais = votosNominaisPorPartido[partido->getSigla()];
        
        std::string candidatosText = (eleitos == 1) ? "candidato eleito" : "candidatos eleitos";
        std::string nominaisText = (nominais == 1) ? "nominal" : "nominais";
        
        std::cout << (i + 1) << " - " << partido->getSigla() << " - " << partido->getNumero() 
                  << ", " << formatarNumero(partido->getTotalVotos()) << " votos (" 
                  << formatarNumero(nominais) << " " << nominaisText << " e " 
                  << formatarNumero(partido->getVotosLegenda()) << " de legenda), " 
                  << eleitos << " " << candidatosText << std::endl;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio7PrimeiroUltimoColocados() {
    std::cout << "Primeiro e último colocados de cada partido:" << std::endl;
    
    // Agrupa candidatos por partido (apenas com votos > 0)
    std::map<std::string, std::vector<Candidato*>> candidatosPorPartido;
    for (const auto& candidato : candidatos_) {
        if (candidato->getVotosRecebidos() > 0) {
            candidatosPorPartido[candidato->getPartido()->getSigla()].push_back(candidato.get());
        }
    }
    
    // Calcula o mais votado de cada partido para ordenação
    std::map<std::string, int> maisVotadoPorPartido;
    for (auto& par : candidatosPorPartido) {
        if (!par.second.empty()) {
            int maxVotos = 0;
            for (const auto& candidato : par.second) {
                maxVotos = std::max(maxVotos, candidato->getVotosRecebidos());
            }
            maisVotadoPorPartido[par.first] = maxVotos;
        }
    }
    
    // Ordena partidos
    std::vector<std::string> partidosOrdenados;
    for (const auto& par : candidatosPorPartido) {
        partidosOrdenados.push_back(par.first);
    }
    
    std::sort(partidosOrdenados.begin(), partidosOrdenados.end(),
              [&](const std::string& p1, const std::string& p2) {
                  int votos1 = maisVotadoPorPartido[p1];
                  int votos2 = maisVotadoPorPartido[p2];
                  if (votos1 != votos2) {
                      return votos1 > votos2;
                  }
                  return getNumeroPartido(p1) < getNumeroPartido(p2);
              });
    
    int posicao = 1;
    for (const auto& siglaPartido : partidosOrdenados) {
        auto& candidatos = candidatosPorPartido[siglaPartido];
        
        std::sort(candidatos.begin(), candidatos.end(),
                  [](const Candidato* a, const Candidato* b) {
                      return Candidato::compararPorVotosEIdade(*a, *b);
                  });
        
        const auto& primeiro = candidatos[0];
        const auto& ultimo = candidatos[candidatos.size() - 1];
        
        std::cout << posicao << " - " << siglaPartido << " - " << primeiro->getPartido()->getNumero()
                  << ", " << primeiro->getNomeUrna() << " (" << primeiro->getNumeroCandidato() 
                  << ", " << formatarNumero(primeiro->getVotosRecebidos()) << " votos) / "
                  << ultimo->getNomeUrna() << " (" << ultimo->getNumeroCandidato() 
                  << ", " << formatarNumero(ultimo->getVotosRecebidos()) << " votos)" << std::endl;
        
        posicao++;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio8DistribuicaoIdade() {
    std::cout << "Eleitos, por faixa etária (na data da eleição):" << std::endl;
    
    std::map<std::string, int> faixasEtarias = {
        {"Idade < 30", 0},
        {"30 <= Idade < 40", 0},
        {"40 <= Idade < 50", 0},
        {"50 <= Idade < 60", 0},
        {"60 <= Idade", 0}
    };
    
    for (const auto& candidato : candidatos_) {
        if (candidato->isEleito()) {
            int idade = candidato->getIdade(dataEleicao_);
            
            if (idade < 30) {
                faixasEtarias["Idade < 30"]++;
            } else if (idade < 40) {
                faixasEtarias["30 <= Idade < 40"]++;
            } else if (idade < 50) {
                faixasEtarias["40 <= Idade < 50"]++;
            } else if (idade < 60) {
                faixasEtarias["50 <= Idade < 60"]++;
            } else {
                faixasEtarias["60 <= Idade"]++;
            }
        }
    }
    
    std::vector<std::string> ordem = {"Idade < 30", "30 <= Idade < 40", "40 <= Idade < 50", 
                                     "50 <= Idade < 60", "60 <= Idade"};
    
    for (const auto& faixa : ordem) {
        int quantidade = faixasEtarias[faixa];
        double percentual = (quantidade * 100.0) / numeroVagas_;
        std::cout << faixa << ": " << quantidade << " (" 
                  << std::fixed << std::setprecision(2) << percentual << "%)" << std::endl;
    }
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio9DistribuicaoGenero() {
    std::cout << "Eleitos, por gênero:" << std::endl;
    
    int feminino = 0, masculino = 0;
    
    for (const auto& candidato : candidatos_) {
        if (candidato->isEleito()) {
            if (candidato->getGenero() == Genero::FEMININO) {
                feminino++;
            } else {
                masculino++;
            }
        }
    }
    
    double percentualFeminino = (feminino * 100.0) / numeroVagas_;
    double percentualMasculino = (masculino * 100.0) / numeroVagas_;
    
    std::cout << "Feminino: " << feminino << " (" 
              << std::fixed << std::setprecision(2) << percentualFeminino << "%)" << std::endl;
    std::cout << "Masculino: " << masculino << " (" 
              << std::fixed << std::setprecision(2) << percentualMasculino << "%)" << std::endl;
    std::cout << std::endl;
}

void GeradorRelatorios::relatorio10TotalVotos() {
    int totalVotos = calcularTotalVotos();
    int votosNominais = calcularVotosNominais();
    int votosLegenda = calcularVotosLegenda();
    
    std::cout << "Total de votos válidos: " << formatarNumero(totalVotos) << std::endl;
    std::cout << "Total de votos nominais: " << formatarNumero(votosNominais) << " (" 
              << std::fixed << std::setprecision(2) << calcularPercentualNominais() << "%)" << std::endl;
    std::cout << "Total de votos de legenda: " << formatarNumero(votosLegenda) << " (" 
              << std::fixed << std::setprecision(2) << calcularPercentualLegenda() << "%)" << std::endl;
}

int GeradorRelatorios::calcularTotalVotos() const {
    return calcularVotosNominais() + calcularVotosLegenda();
}

int GeradorRelatorios::calcularVotosNominais() const {
    int total = 0;
    for (const auto& candidato : candidatos_) {
        if (!candidato->votosVaoParaLegenda()) {
            total += candidato->getVotosRecebidos();
        }
    }
    return total;
}

int GeradorRelatorios::calcularVotosLegenda() const {
    int total = 0;
    for (const auto& par : partidos_) {
        total += par.second->getVotosLegenda();
    }
    return total;
}

double GeradorRelatorios::calcularPercentualNominais() const {
    int total = calcularTotalVotos();
    return total > 0 ? (calcularVotosNominais() * 100.0) / total : 0.0;
}

double GeradorRelatorios::calcularPercentualLegenda() const {
    int total = calcularTotalVotos();
    return total > 0 ? (calcularVotosLegenda() * 100.0) / total : 0.0;
}

std::string GeradorRelatorios::getNumeroPartido(const std::string& sigla) const {
    for (const auto& par : partidos_) {
        if (par.second->getSigla() == sigla) {
            return par.second->getNumero();
        }
    }
    return "";
}

std::string GeradorRelatorios::formatarNumero(int numero) const {
    std::ostringstream oss;
    oss.imbue(std::locale(""));
    oss << numero;
    return oss.str();
}