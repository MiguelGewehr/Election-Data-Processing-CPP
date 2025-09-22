#include "Candidato.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <locale>

Candidato::Candidato(TipoDeputado cargo, const std::string& numeroCandidato, const std::string& nomeUrna,
                     std::shared_ptr<Partido> partido, std::unique_ptr<Federacao> federacao,
                     const Date& dataNascimento, Genero genero, bool eleito, bool votosVaoParaLegenda)
    : cargo_(cargo), numeroCandidato_(numeroCandidato), nomeUrna_(nomeUrna), partido_(partido),
      federacao_(std::move(federacao)), dataNascimento_(dataNascimento), genero_(genero),
      eleito_(eleito), votosVaoParaLegenda_(votosVaoParaLegenda), votosRecebidos_(0) {
    
    if (numeroCandidato.empty()) {
        throw std::invalid_argument("Número do candidato não pode ser nulo");
    }
    if (nomeUrna.empty()) {
        throw std::invalid_argument("Nome de urna não pode ser nulo");
    }
    if (!partido) {
        throw std::invalid_argument("Partido não pode ser nulo");
    }
}

TipoDeputado Candidato::getCargo() const {
    return cargo_;
}

const std::string& Candidato::getNumeroCandidato() const {
    return numeroCandidato_;
}

const std::string& Candidato::getNomeUrna() const {
    return nomeUrna_;
}

std::shared_ptr<Partido> Candidato::getPartido() const {
    return partido_;
}

const Federacao* Candidato::getFederacao() const {
    return federacao_.get();
}

const Date& Candidato::getDataNascimento() const {
    return dataNascimento_;
}

Genero Candidato::getGenero() const {
    return genero_;
}

bool Candidato::isEleito() const {
    return eleito_;
}

bool Candidato::votosVaoParaLegenda() const {
    return votosVaoParaLegenda_;
}

int Candidato::getVotosRecebidos() const {
    return votosRecebidos_;
}

bool Candidato::pertenceFederacao() const {
    return federacao_ && federacao_->isValida();
}

void Candidato::adicionarVotos(int votos) {
    if (votos < 0) {
        throw std::invalid_argument("Número de votos não pode ser negativo");
    }
    votosRecebidos_ += votos;
}

int Candidato::getIdade(const Date& dataReferencia) const {
    auto nascimento = std::chrono::sys_days{dataNascimento_};
    auto referencia = std::chrono::sys_days{dataReferencia};
    auto diff = referencia - nascimento;
    return static_cast<int>(diff.count() / 365);
}

bool Candidato::compararPorVotosEIdade(const Candidato& c1, const Candidato& c2) {
    // Primeiro critério: votos (decrescente)
    if (c1.getVotosRecebidos() != c2.getVotosRecebidos()) {
        return c1.getVotosRecebidos() > c2.getVotosRecebidos();
    }
    
    // Em caso de empate, candidato mais velho (nascimento anterior) tem prioridade
    return c1.getDataNascimento() < c2.getDataNascimento();
}

std::string Candidato::formatarParaRelatorio() const {
    std::string prefixoFederacao = pertenceFederacao() ? "*" : "";
    
    std::ostringstream oss;
    oss.imbue(std::locale(""));
    oss << prefixoFederacao << nomeUrna_ << " (" << partido_->getSigla() 
        << ", " << votosRecebidos_ << " votos)";
    
    return oss.str();
}

std::string Candidato::toString() const {
    std::ostringstream oss;
    oss << "Candidato{numero='" << numeroCandidato_ << "', nome='" << nomeUrna_
        << "', partido=" << partido_->getSigla() << ", cargo=" << static_cast<int>(cargo_)
        << ", genero=" << static_cast<int>(genero_) << ", eleito=" << std::boolalpha << eleito_;
    
    if (pertenceFederacao()) {
        oss << ", federacao=" << federacao_->getNumero();
    }
    
    if (votosVaoParaLegenda_) {
        oss << ", votosParaLegenda=true";
    }
    
    oss << ", votos=" << votosRecebidos_ << "}";
    
    return oss.str();
}

bool Candidato::operator==(const Candidato& other) const {
    return numeroCandidato_ == other.numeroCandidato_ && cargo_ == other.cargo_;
}

bool Candidato::operator!=(const Candidato& other) const {
    return !(*this == other);
}