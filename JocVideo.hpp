#ifndef JOCVIDEO_HPP
#define JOCVIDEO_HPP

#include <string>

class JocVideo {
public:
    JocVideo(const std::string& nume, double pret);

    JocVideo(std::string nume, double pret);

    virtual ~JocVideo();

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] double getPret() const;

    [[nodiscard]] virtual JocVideo* clone() const = 0;
    virtual void afiseazaDetalii() const = 0;

private:
    std::string nume;
    double pret;

    [[maybe_unused]] void incepeJoc() const;
};

#endif // JOCVIDEO_HPP
