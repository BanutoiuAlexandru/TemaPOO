#ifndef JOCRPG_HPP
#define JOCRPG_HPP

#include "JocVideo.hpp"

class [[maybe_unused]] JocRPG : public JocVideo {
public:
    [[maybe_unused]] JocRPG(const std::string& nume, double pret);

    [[maybe_unused]] void afiseazaDetalii() const override ;
};

#endif // JOCRPG_HPP