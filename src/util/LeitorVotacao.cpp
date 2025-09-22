#include "LeitorVotacao.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <locale>

const std::vector<std::string> LeitorVotacao::VOTOS_INVALIDOS = {"95", "96", "97", "98"};

void LeitorVotacao::lerVotacao(const std::string& arquivo,
                              std::vector<std::unique_ptr<Candidato>>& candidatos,
                              std::map<std::string, std::shared_ptr<Partido>>& partidos,
                              TipoDeputado tipoDesejado) {
    
    // Cria índices para busca rápida
    std::map<std::string, Candidato*> candidatosPorNumero;
    for (auto& candidato : candidatos) {
        candidatosPorNumero[candidato->getNumeroCandidato()] = candidato.get();
    }
    
    int totalLinhas = 0;
    
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de votação: " + arquivo);
    }
    
    std::string linha;
    
    // Pula o cabeçalho
    if (!std::getline(file, linha)) {
        throw std::runtime_error("Arquivo de votação vazio ou inválido");
    }
    
    std::cout << "=== LENDO ARQUIVO DE VOTAÇÃO ===" << std::endl;
    std::cout << "Processando arquivo: " << arquivo << std::endl;
    std::cout << "Encoding: " << ENCODING << std::endl;
    std::cout << "Filtrando para: " << tipoDeputadoToString(tipoDesejado) << std::endl;
    
    while (std::getline(file, linha)) {
        totalLinhas++;
        
        try {
            processarLinhaVotacao(linha, candidatosPorNumero, partidos, tipoDesejado);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar linha de votação " << (totalLinhas + 1) 
                      << ": " << e.what() << std::endl;
        }
    }
    
    file.close();
}

void LeitorVotacao::processarLinhaVotacao(const std::string& linha,
                                         std::map<std::string, Candidato*>& candidatos,
                                         std::map<std::string, std::shared_ptr<Partido>>& partidos,
                                         TipoDeputado tipoDesejado) {
    
    auto campos = split(linha, SEPARATOR);
    
    if (campos.size() < 22) {
        throw std::invalid_argument("Linha de votação com número insuficiente de campos");
    }
    
    int codigoCargo = parseInt(campos[CD_CARGO]);
    if (codigoCargo != getCodigoTipoDeputado(tipoDesejado)) {
        return; // Não é do tipo desejado
    }
    
    std::string nrVotavel = parseString(campos[NR_VOTAVEL]);
    int qtVotos = parseInt(campos[QT_VOTOS]);
    
    if (isVotoInvalido(nrVotavel)) {
        return; // Voto inválido
    }
    
    // Tenta encontrar um candidato com o número votado
    auto candidatoIt = candidatos.find(nrVotavel);
    if (candidatoIt != candidatos.end()) {
        Candidato* candidato = candidatoIt->second;
        candidato->adicionarVotos(qtVotos);
        
        if (candidato->votosVaoParaLegenda()) {
            candidato->getPartido()->adicionarVotosLegenda(qtVotos);
        } else {
            candidato->getPartido()->adicionarVotosNominais(qtVotos);
        }
    } 
    // Se não for candidato, verifica se é um partido (voto de legenda)
    else {
        auto partidoIt = partidos.find(nrVotavel);
        if (partidoIt != partidos.end()) {
            partidoIt->second->adicionarVotosLegenda(qtVotos);
        }
    }
}

bool LeitorVotacao::isVotoInvalido(const std::string& nrVotavel) {
    return std::find(VOTOS_INVALIDOS.begin(), VOTOS_INVALIDOS.end(), nrVotavel) 
           != VOTOS_INVALIDOS.end();
}

std::string LeitorVotacao::parseString(const std::string& campo) {
    if (campo.empty() || campo.length() < 2) {
        throw std::invalid_argument("Campo inválido: " + campo);
    }
    return campo.substr(1, campo.length() - 2);
}

int LeitorVotacao::parseInt(const std::string& campo) {
    try {
        return std::stoi(parseString(campo));
    } catch (const std::exception& e) {
        throw std::invalid_argument("Não foi possível converter para inteiro: " + campo);
    }
}

std::vector<std::string> LeitorVotacao::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}