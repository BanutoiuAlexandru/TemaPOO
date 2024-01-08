#ifndef APLICATIE_HPP
#define APLICATIE_HPP

#pragma once
#include "Utilizator.hpp"
#include "Magazin.hpp"
#include "JocRPG.hpp"
#include "JocVideo.hpp"
#include <unordered_map>

class Aplicatie {
private:
    std::unordered_map<std::string, Utilizator> utilizatoriMap;
    std::vector<Utilizator> utilizatori;
    Magazin magazin;

    void incarcaUtilizatori();
    void incarcaJocuri();
    void logare();
    void creareCont();

public:
    Aplicatie();
    void run();
};

#endif