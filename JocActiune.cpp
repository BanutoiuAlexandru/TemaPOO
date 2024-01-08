#include "JocActiune.hpp"
#include <iostream>

void JocActiune::ruleaza() const {
}

void JocActiune::afiseazaDetalii() const {
    std::cout << "Nume Joc: " << getNume() << ", Pret: " << getPret() << ", Nivel Dificultate: " << nivelDificultate << std::endl;
}

[[maybe_unused]] JocVideo* JocActiune::clone() const {
    return new JocActiune(*this);
}
