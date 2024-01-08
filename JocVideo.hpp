#ifndef JOCVIDEO_HPP
#define JOCVIDEO_HPP

#include <string>

class JocVideo {
private:
    std::string nume;
    double pret;
public:

    JocVideo(std::string  nume, double pret);


    [[maybe_unused]] virtual void ruleaza() const = 0;


    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] double getPret() const;

    [[maybe_unused]] [[maybe_unused]] virtual void incepeJoc() const;

    [[maybe_unused]] virtual void ruleaza() = 0;
    virtual ~JocVideo() = default;
    virtual void afiseazaDetalii() const = 0;
};

#endif // JOCVIDEO_HPP
