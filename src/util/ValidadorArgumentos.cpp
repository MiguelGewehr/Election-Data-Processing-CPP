#include "ValidadorArgumentos.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <regex>
#include <chrono>
#include <sstream>
#include <iomanip>

void ValidadorArgumentos::validar(const std::vector<std::string>& args) {
    if (args.size() != 4) {
        mostrarUso();
        throw std::invalid_argument("Número incorreto de argumentos");
    }
    
    validarTipoDeputado(args[0]);
    validarArquivo(args[1], "candidatos");
    validarArquivo(args[2], "votação");
    validarData(args[3]);
}

void ValidadorArgumentos::validarTipoDeputado(const std::string& tipo) {
    if (tipo != "--federal" && tipo != "--estadual") {
        throw std::invalid_argument(
            "Tipo de deputado deve ser --federal ou --estadual, recebido: " + tipo
        );
    }
}

void ValidadorArgumentos::validarArquivo(const std::string& caminho, const std::string& tipo) {
    std::ifstream arquivo(caminho);
    
    if (!arquivo.good()) {
        throw std::invalid_argument(
            "Arquivo de " + tipo + " não encontrado ou não pode ser lido: " + caminho
        );
    }
    arquivo.close();
}

void ValidadorArgumentos::validarData(const std::string& data) {
    std::regex dateRegex(R"(\d{2}/\d{2}/\d{4})");
    if (!std::regex_match(data, dateRegex)) {
        throw std::invalid_argument(
            "Data inválida. Use o formato dd/mm/yyyy. Recebido: " + data
        );
    }
    
    // Tenta fazer o parse para verificar se é uma data válida
    try {
        parseData(data);
    } catch (const std::exception&) {
        throw std::invalid_argument(
            "Data inválida. Use o formato dd/mm/yyyy. Recebido: " + data
        );
    }
}

Date ValidadorArgumentos::parseData(const std::string& data) {
    std::regex dateRegex(R"((\d{2})/(\d{2})/(\d{4}))");
    std::smatch matches;
    
    if (!std::regex_match(data, matches, dateRegex)) {
        throw std::invalid_argument("Erro ao converter data: " + data);
    }
    
    int dia = std::stoi(matches[1].str());
    int mes = std::stoi(matches[2].str());
    int ano = std::stoi(matches[3].str());
    
    // Validação básica
    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        throw std::invalid_argument("Data inválida: " + data);
    }
    
    return Date{std::chrono::year{ano}, std::chrono::month{static_cast<unsigned int>(mes)}, std::chrono::day{static_cast<unsigned int>(dia)}};
}

std::string ValidadorArgumentos::formatarData(const Date& data) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << static_cast<unsigned>(data.day()) << "/"
        << std::setfill('0') << std::setw(2) << static_cast<unsigned>(data.month()) << "/"
        << static_cast<int>(data.year());
    return oss.str();
}

void ValidadorArgumentos::mostrarUso() {
    std::cerr << "Uso: ./deputados <tipo> <candidatos.csv> <votacao.csv> <data>" << std::endl;
    std::cerr << "  <tipo>: --federal ou --estadual" << std::endl;
    std::cerr << "  <data>: formato dd/mm/yyyy" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Exemplos:" << std::endl;
    std::cerr << "  ./deputados --federal candidatos.csv votacao.csv 02/10/2022" << std::endl;
    std::cerr << "  ./deputados --estadual candidatos.csv votacao.csv 02/10/2022" << std::endl;
}