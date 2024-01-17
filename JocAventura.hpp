#ifndef JOC_AVENTURA_HPP
#define JOC_AVENTURA_HPP

#include "JocVideo.hpp"

class [[maybe_unused]] JocAventura : public JocVideo {
public:
    [[maybe_unused]] JocAventura(const std::string& nume, double pret, std::string  tipAventura);

    [[maybe_unused]] void ruleaza() const ;
    [[maybe_unused]] void afiseazaDetalii() const ;
    [[maybe_unused]] [[nodiscard]] JocAventura* clone() const override;

private:
    std::string tipAventura;
};

#endif // JOC_AVENTURA_HPP
