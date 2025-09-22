#include "Federacao.h"

Federacao::Federacao(int numero) : numero_(numero) {}

int Federacao::getNumero() const {
    return numero_;
}

bool Federacao::isValida() const {
    return numero_ != -1;
}

std::string Federacao::toString() const {
    return "Federacao{numero=" + std::to_string(numero_) + "}";
}

bool Federacao::operator==(const Federacao& other) const {
    return numero_ == other.numero_;
}

bool Federacao::operator!=(const Federacao& other) const {
    return !(*this == other);
}