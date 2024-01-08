#include "Utilizator.hpp"

Utilizator::Utilizator() : nume(), parola(), balanta(0.0), balantaFantoma(nullptr) {}

Utilizator::Utilizator(std::string& nume, std::string& parola, double balanta)
        : nume(nume), parola(parola), balanta(balanta), balantaFantoma(nullptr) {}

Utilizator::Utilizator(const Utilizator& other)
        : nume(other.nume), parola(other.parola), balanta(other.balanta),
          balantaFantoma(other.balantaFantoma ? new double(*(other.balantaFantoma)) : nullptr) {}

Utilizator::~Utilizator() {
    delete balantaFantoma;
}

Utilizator& Utilizator::operator=(const Utilizator& other) {
    if (this != &other) {
        nume = other.nume;
        parola = other.parola;
        balanta = other.balanta;

        delete balantaFantoma;

        balantaFantoma = (other.balantaFantoma ? new double(*(other.balantaFantoma)) : nullptr);
    }
    return *this;
}

const std::string& Utilizator::getNume() const {
    return nume;
}

const std::string& Utilizator::getParola() const {
    return parola;
}

double Utilizator::getBalanta() const {
    return balanta;
}

const double* Utilizator::getBalantaFantoma() const {
    return balantaFantoma;
}

void Utilizator::adaugaBani(double suma) {
    if (suma >= 0.0) {
        balanta += suma;
        std::cout << "Balanta actualizata cu succes.\n";
    } else {
        std::cout << "Suma introdusa este invalida. Va rugam sa introduceti o valoare mai mare sau egala cu 0.\n";
    }
}

void Utilizator::adaugaJocCumparat(JocVideo* joc) {
    jocuriCumparate.push_back(joc);
}

void Utilizator::afiseazaJocuriCumparate() const {
    if (jocuriCumparate.empty()) {
        std::cout << "Nu ati cumparat inca niciun joc.\n";
    } else {
        std::cout << "Jocuri Cumparate:\n";
        for (const auto& joc : jocuriCumparate) {
            joc->afiseazaDetalii();
            std::cout << std::endl;
        }
    }
}
