#include <iostream>
#include "JocStrategie.hpp"

[[maybe_unused]] JocStrategie::JocStrategie(std::string& nume, double pret, std::string& tipStrategie)
        : JocVideo(nume, pret), tipStrategie(tipStrategie) {}

[[maybe_unused]] void JocStrategie::afiseazaDetalii() const {
    std::cout << "Nume Joc: " << getNume() << ", Pret: " << getPret() << ", Tip Strategie: " << tipStrategie << std::endl;
}

[[maybe_unused]] JocVideo *JocStrategie::clone() {
    return nullptr;
}

//[[maybe_unused]] JocVideo* JocStrategie::clone() const {
  //  return new JocStrategie(*this);
//}
