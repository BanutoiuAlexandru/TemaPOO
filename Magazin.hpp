#ifndef MAGAZIN_HPP
#define MAGAZIN_HPP

#include <iostream>
#include <vector>
#include "JocVideo.hpp"

class Magazin {
private:
    std::vector<JocVideo*> jocuriDisponibile;

public:
    [[nodiscard]] const std::vector<JocVideo*>& getJocuriDisponibile() const;

    [[maybe_unused]] void adaugaJoc(JocVideo* joc);
    void afiseazaJocuri() const;
    [[nodiscard]] const JocVideo* getJoc(std::size_t index) const;

};

#endif
