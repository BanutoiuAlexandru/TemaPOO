#ifndef JOCSTRATEGIE_HPP
#define JOCSTRATEGIE_HPP

#include "JocVideo.hpp"

class [[maybe_unused]] JocStrategie : public JocVideo {
private:
    std::string tipStrategie;

public:
    [[maybe_unused]] JocStrategie(std::string& nume, double pret, std::string& tipStrategie);

    [[maybe_unused]] void afiseazaDetalii() const override;

    [[maybe_unused]] [[maybe_unused]] [[nodiscard]] static JocVideo* clone() ;
};

#endif // JOCSTRATEGIE_HPP
