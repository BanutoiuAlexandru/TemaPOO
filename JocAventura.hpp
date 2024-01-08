#pragma once
#include "JocVideo.hpp"
#include <iostream>
#include <utility>

class [[maybe_unused]] JocAventura : public JocVideo {
private:
    std::string tipAventura;

public:
    [[maybe_unused]] JocAventura(const std::string& nume, double pret, std::string  tip)
            : JocVideo(nume, pret), tipAventura(std::move(tip)) {}

    void ruleaza() const override;
    void afiseazaDetalii() const override;

    [[maybe_unused]] [[nodiscard]] JocVideo* clone() const ;
};
