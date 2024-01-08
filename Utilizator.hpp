#ifndef UTILIZATOR_HPP
#define UTILIZATOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include "JocVideo.hpp"

class Utilizator {
private:
    std::string nume;
    std::string parola;
    double balanta;
    double* balantaFantoma;
    std::vector<JocVideo*> jocuriCumparate;

public:
    Utilizator();
    Utilizator(std::string& nume, std::string& parola, double balanta);
    Utilizator(const Utilizator& other);
    ~Utilizator();

    Utilizator& operator=(const Utilizator& other);

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getParola() const;
    [[nodiscard]] double getBalanta() const;
    [[maybe_unused]] [[nodiscard]] const double* getBalantaFantoma() const;

    void adaugaBani(double suma);
    void adaugaJocCumparat(JocVideo* joc);
    void afiseazaJocuriCumparate() const;
};

#endif
