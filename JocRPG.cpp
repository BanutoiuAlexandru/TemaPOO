#include "JocRPG.hpp"
#include <iostream>

[[maybe_unused]] JocRPG::JocRPG(const std::string& nume, double pret) : JocVideo(nume, pret) {
}

[[maybe_unused]] void JocRPG::afiseazaDetalii() const {
    std::cout << "Joc RPG: " << getNume() << ", Pret: " << getPret() << std::endl;
}
