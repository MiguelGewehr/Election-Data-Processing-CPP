#include "LeitorCandidatos.h"
#include "../model/enums/Genero.h"
#include "ValidadorArgumentos.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <locale>

std::map<std::string, std::shared_ptr<Partido>> LeitorCandidatos::partidosCache_;

std::vector<std::unique_ptr<Candidato>> LeitorCandidatos::lerCandidatos(
    const std::string& arquivo, TipoDeputado tipoDesejado) {
    
    std::vector<std::unique_ptr<Candidato>> candidatos;
    partidosCache_.clear(); // Limpa o cache de partidos
    
    int totalLinhas = 0;
    std::map<int, int> cargosCounts;
    
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo: " + arquivo);
    }
    
    try {
        // Tenta um nome de locale comum para ISO-8859-1 em sistemas POSIX
        file.imbue(std::locale("pt_BR.iso88591"));
    } catch (const std::runtime_error& e) {
        std::cerr << "Aviso: Não foi possível definir o locale 'pt_BR.iso88591'. Tentando alternativa..." << std::endl;
        try {
            // Tenta um nome de locale mais genérico
            file.imbue(std::locale(""));
        } catch (const std::runtime_error& e2) {
            std::cerr << "Aviso: Não foi possível definir um locale padrão. A acentuação pode não ser exibida corretamente." << std::endl;
        }
    }
    
    std::string linha;
    
    // Pula o cabeçalho
    if (!std::getline(file, linha)) {
        throw std::runtime_error("Arquivo vazio ou inválido");
    }
    
    while (std::getline(file, linha)) {
        totalLinhas++;
        
        try {
            auto candidato = processarLinha(linha, tipoDesejado, cargosCounts);
            if (candidato) {
                candidatos.push_back(std::move(candidato));
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar linha " << (totalLinhas + 1) << ": " 
                      << e.what() << std::endl;
            // Continua processamento mesmo com erros individuais
        }
    }
    
    file.close();
    
    // Mostra estatísticas de cargos encontrados
    if (!cargosCounts.empty()) {
        std::cout << "\nEstatísticas de cargos no arquivo:" << std::endl;
        for (const auto& [codigo, count] : cargosCounts) {
            std::cout << "- Cargo " << codigo << " (" << getNomeCargo(codigo) 
                      << "): " << count << " candidatos" << std::endl;
        }
    }
    
    std::cout << std::endl;
    return candidatos;
}


std::unique_ptr<Candidato> LeitorCandidatos::processarLinha(
    const std::string& linha, TipoDeputado tipoDesejado, std::map<int, int>& cargosCounts) {
    
    auto campos = split(linha, SEPARATOR);
    
    if (campos.size() < 70) { // Verifica se tem campos suficientes
        throw std::invalid_argument("Linha com número insuficiente de campos");
    }
    
    // Verifica cargo
    int codigoCargo = parseInt(campos[CD_CARGO]);
    cargosCounts[codigoCargo]++;
    
    // Se não é deputado federal ou estadual
    if (codigoCargo != 6 && codigoCargo != 7) {
        return nullptr; // Não é deputado, ignora
    }
    
    TipoDeputado cargo = tipoDeputadoFromCodigo(codigoCargo);
    if (cargo != tipoDesejado) {
        return nullptr; // É deputado, mas não do tipo desejado
    }
    
    // Verifica situação do candidato
    int situacao = parseInt(campos[CD_SITUACAO_CANDIDADO_TOT]);
    bool votosParaLegenda = parseString(campos[NM_TIPO_DESTINACAO_VOTOS]) == VOTOS_LEGENDA_MARKER;
    
    // Processa apenas candidatos válidos ou com votos para legenda
    if (situacao != 2 && situacao != 16 && !votosParaLegenda) {
        return nullptr;
    }
    
    // Extrai dados do candidato
    std::string numeroCandidato = parseString(campos[NR_CANDIDATO]);
    std::string nomeUrna = parseString(campos[NM_URNA_CANDIDATO]);
    std::string numeroPartido = parseString(campos[NR_PARTIDO]);
    std::string siglaPartido = parseString(campos[SG_PARTIDO]);
    int numeroFederacao = parseInt(campos[NR_FEDERACAO]);
    Date dataNascimento = parseData(campos[DT_NASCIMENTO]);
    Genero genero = generoFromCodigo(parseInt(campos[CD_GENERO]));
    
    // Verifica se candidato foi eleito
    int situacaoTurno = parseInt(campos[CD_SIT_TOT_TURNO]);
    bool eleito = (situacaoTurno == 2 || situacaoTurno == 3);
    
    // Obtém ou cria partido
    auto it = partidosCache_.find(numeroPartido);
    std::shared_ptr<Partido> partido;
    if (it != partidosCache_.end()) {
        partido = it->second;
    } else {
        partido = std::make_shared<Partido>(numeroPartido, siglaPartido);
        partidosCache_[numeroPartido] = partido;
    }
    
    // Cria federação
    std::unique_ptr<Federacao> federacao = nullptr;
    if (numeroFederacao != -1) {
        federacao = std::make_unique<Federacao>(numeroFederacao);
    }
    
    return std::make_unique<Candidato>(cargo, numeroCandidato, nomeUrna, partido,
                                      std::move(federacao), dataNascimento, genero,
                                      eleito, votosParaLegenda);
}

std::string LeitorCandidatos::parseString(const std::string& campo) {
    if (campo.empty() || campo.length() < 2) {
        throw std::invalid_argument("Campo inválido: " + campo);
    }
    // Remove aspas do início e fim
    return campo.substr(1, campo.length() - 2);
}

int LeitorCandidatos::parseInt(const std::string& campo) {
    try {
        return std::stoi(parseString(campo));
    } catch (const std::exception& e) {
        throw std::invalid_argument("Não foi possível converter para inteiro: " + campo);
    }
}

Date LeitorCandidatos::parseData(const std::string& campo) {
    return ValidadorArgumentos::parseData(parseString(campo));
}

std::vector<std::string> LeitorCandidatos::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::map<std::string, std::shared_ptr<Partido>> LeitorCandidatos::getPartidosCarregados() {
    return partidosCache_;
}