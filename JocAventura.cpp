// JocAventura.cpp

#include "JocAventura.hpp"
#include <iostream>
#include <utility>

[[maybe_unused]] JocAventura::JocAventura(const std::string& nume, double pret, std::string  tipAventura)
        : JocVideo(nume, pret), tipAventura(std::move(tipAventura)) {}

[[maybe_unused]] void JocAventura::ruleaza() const {
    // Implementare pentru ruleaza, dacă este necesar
}

[[maybe_unused]] void JocAventura::afiseazaDetalii() const {
    std::cout << "Nume Joc: " << getNume() << ", Pret: " << getPret() << ", Tip Aventura: " << tipAventura << std::endl;
}

[[maybe_unused]] JocAventura* JocAventura::clone() const {
    return new JocAventura(*this);
}
