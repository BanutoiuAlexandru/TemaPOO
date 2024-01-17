#include "JocVideo.hpp"
#include <iostream>
#include <utility>

JocVideo::JocVideo(std::string nume, double pret) : nume(std::move(nume)), pret(pret) {}

JocVideo::~JocVideo() = default;

const std::string& JocVideo::getNume() const {
    return nume;
}

double JocVideo::getPret() const {
    return pret;
}

[[maybe_unused]] [[maybe_unused]] [[maybe_unused]] void JocVideo::incepeJoc() const {
    std::cout << "Incepe jocul generic: " << nume << std::endl;
}
