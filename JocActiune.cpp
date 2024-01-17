#include "JocActiune.hpp"
#include <iostream>

[[maybe_unused]] void JocActiune::ruleaza() const {
}

[[maybe_unused]] void JocActiune::afiseazaDetalii() const {
    std::cout << "Nume Joc: " << getNume() << ", Pret: " << getPret() << ", Nivel Dificultate: " << nivelDificultate << std::endl;
}

[[maybe_unused]] JocVideo* JocActiune::clone() const {
    return new JocActiune(*this);
}
