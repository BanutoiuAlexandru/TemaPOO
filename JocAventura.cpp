#include "JocAventura.hpp"
#include <iostream>

void JocAventura::ruleaza() const {
    // Implementare pentru ruleaza, dacă este necesar
}

void JocAventura::afiseazaDetalii() const {
    std::cout << "Nume Joc: " << getNume() << ", Pret: " << getPret() << ", Tip Aventura: " << tipAventura << std::endl;
}

[[maybe_unused]] JocVideo* JocAventura::clone() const {
    return new JocAventura(*this);
}
