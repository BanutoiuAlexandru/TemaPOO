#include "Magazin.hpp"

const std::vector<JocVideo*>& Magazin::getJocuriDisponibile() const {
    return jocuriDisponibile;
}

[[maybe_unused]] void Magazin::adaugaJoc(JocVideo* joc) {
    jocuriDisponibile.push_back(joc);
}

void Magazin::afiseazaJocuri() const {
    int index = 1;
    for (const auto& joc : jocuriDisponibile) {
        std::cout << index << ". ";
        joc->afiseazaDetalii();
        std::cout << std::endl;
        index++;
    }
}

[[maybe_unused]] const JocVideo* Magazin::getJoc(std::size_t index) const {
    if (index < jocuriDisponibile.size()) {
        return jocuriDisponibile[index];
    } else {
        throw std::out_of_range("Index out of bounds");
    }
}

