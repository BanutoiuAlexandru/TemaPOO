#pragma once
#include "JocVideo.hpp"
#include <iostream>
#include <utility>

class [[maybe_unused]] JocActiune : public JocVideo {
private:
    std::string nivelDificultate;

public:
    [[maybe_unused]] JocActiune(const std::string& nume, double pret, std::string  dificultate)
            : JocVideo(nume, pret), nivelDificultate(std::move(dificultate)) {}

    [[maybe_unused]] void ruleaza() const override;

    [[maybe_unused]] void afiseazaDetalii() const override;

    [[maybe_unused]] [[nodiscard]] JocVideo* clone() const ;
};
