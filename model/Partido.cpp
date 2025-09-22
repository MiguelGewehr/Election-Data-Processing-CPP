#include "Partido.h"
#include <algorithm>
#include <locale>
#include <iomanip>
#include <sstream>

Partido::Partido(const std::string& numero, const std::string& sigla)
    : numero_(numero), sigla_(sigla), votosNominais_(0), votosLegenda_(0), candidatosEleitos_(0) {
    if (numero.empty()) {
        throw std::invalid_argument("Número do partido não pode ser vazio");
    }
    if (sigla.empty()) {
        throw std::invalid_argument("Sigla do partido não pode ser vazia");
    }
}

const std::string& Partido::getNumero() const {
    return numero_;
}

const std::string& Partido::getSigla() const {
    return sigla_;
}

int Partido::getVotosNominais() const {
    return votosNominais_;
}

int Partido::getVotosLegenda() const {
    return votosLegenda_;
}

int Partido::getTotalVotos() const {
    return votosNominais_ + votosLegenda_;
}

int Partido::getCandidatosEleitos() const {
    return candidatosEleitos_;
}

void Partido::adicionarVotosNominais(int votos) {
    if (votos < 0) {
        throw std::invalid_argument("Votos não podem ser negativos");
    }
    votosNominais_ += votos;
}

void Partido::adicionarVotosLegenda(int votos) {
    if (votos < 0) {
        throw std::invalid_argument("Votos não podem ser negativos");
    }
    votosLegenda_ += votos;
}

void Partido::incrementarCandidatosEleitos() {
    candidatosEleitos_++;
}

bool Partido::compararPorVotosENumero(const Partido& p1, const Partido& p2) {
    // Primeiro critério: total de votos (decrescente)
    if (p1.getTotalVotos() != p2.getTotalVotos()) {
        return p1.getTotalVotos() > p2.getTotalVotos();
    }
    
    // Em caso de empate, menor número partidário tem prioridade
    try {
        int num1 = std::stoi(p1.getNumero());
        int num2 = std::stoi(p2.getNumero());
        return num1 < num2;
    } catch (const std::exception&) {
        return p1.getNumero() < p2.getNumero();
    }
}

std::string Partido::formatarParaRelatorio(int posicao) const {
    std::string candidatosText = (candidatosEleitos_ == 1) ? "candidato eleito" : "candidatos eleitos";
    std::string nominaisText = (votosNominais_ == 1) ? "nominal" : "nominais";
    
    std::ostringstream oss;
    oss.imbue(std::locale(""));
    oss << posicao << " - " << sigla_ << " - " << numero_ << ", " 
        << getTotalVotos() << " votos (" << votosNominais_ << " " << nominaisText
        << " e " << votosLegenda_ << " de legenda), " << candidatosEleitos_ 
        << " " << candidatosText;
    
    return oss.str();
}

std::string Partido::toString() const {
    std::ostringstream oss;
    oss << "Partido{numero='" << numero_ << "', sigla='" << sigla_ 
        << "', votosNominais=" << votosNominais_ << ", votosLegenda=" << votosLegenda_
        << ", totalVotos=" << getTotalVotos() << ", candidatosEleitos=" << candidatosEleitos_ << "}";
    return oss.str();
}

bool Partido::operator==(const Partido& other) const {
    return numero_ == other.numero_;
}

bool Partido::operator!=(const Partido& other) const {
    return !(*this == other);
}