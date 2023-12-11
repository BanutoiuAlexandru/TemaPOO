#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <cstring>

int getch() {
    struct termios oldt, newt;
    int ch;

    // Inițializare completă a structurii termios
    memset(&oldt, 0, sizeof(oldt));
    memset(&newt, 0, sizeof(newt));

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

#endif//_WIN32

class JocVideo {
private:
    std::string nume;
    double pret;

public:
    JocVideo(std::string& nume, double pret)
            : nume(nume), pret(pret) {}

    [[nodiscard]] const std::string& getNume() const {
        return nume;
    }

    [[nodiscard]] double getPret() const {
        return pret;
    }

    friend std::ostream& operator<<(std::ostream& out, const JocVideo& joc);
};

std::ostream& operator<<(std::ostream& out, const JocVideo& joc) {
    out << "Nume Joc: " << joc.getNume() << ", Pret: " << joc.getPret();
    return out;
}

class Utilizator {
private:
    std::string nume;
    std::string parola;
    double balanta;
    double* balantaFantoma;
    std::vector<JocVideo> jocuriCumparate;

public:
    Utilizator() : nume(), parola(), balanta(0.0), balantaFantoma(nullptr) {}

    Utilizator(std::string& nume, std::string& parola, double balanta)
            : nume(nume), parola(parola), balanta(balanta), balantaFantoma(nullptr) {}

    Utilizator(const Utilizator& other)
            : nume(other.nume), parola(other.parola), balanta(other.balanta),
              balantaFantoma(other.balantaFantoma ? new double(*(other.balantaFantoma)) : nullptr) {}

    ~Utilizator() {
        delete balantaFantoma;
    }

    Utilizator& operator=(const Utilizator& other) {
        if (this != &other) {
            nume = other.nume;
            parola = other.parola;
            balanta = other.balanta;

            delete balantaFantoma;

            balantaFantoma = (other.balantaFantoma ? new double(*(other.balantaFantoma)) : nullptr);
        }
        return *this;
    }

    [[nodiscard]] const std::string& getNume() const {
        return nume;
    }

    [[nodiscard]] const std::string& getParola() const {
        return parola;
    }

    [[nodiscard]] double getBalanta() const {
        return balanta;
    }

    [[maybe_unused]] [[nodiscard]] const double* getBalantaFantoma() const {
        return balantaFantoma;
    }

    void adaugaBani(double suma)
    {if (suma >= 0.0) {
            balanta += suma;
            std::cout << "Balanta actualizata cu succes.\n";
        } else {
            std::cout << "Suma introdusa este invalida. Va rugam sa introduceti o valoare mai mare sau egala cu 0.\n";
        }
    }

    void adaugaJocCumparat(const JocVideo& joc) {
        jocuriCumparate.push_back(joc);
    }

    void afiseazaJocuriCumparate() const {
        if (jocuriCumparate.empty()) {
            std::cout << "Nu ati cumparat inca niciun joc.\n";
        } else {
            std::cout << "Jocuri Cumparate:\n";
            for (const auto& joc : jocuriCumparate) {
                std::cout << joc << std::endl;
            }
        }
    }


    friend std::ostream& operator<<(std::ostream& out, const Utilizator& utilizator);
};

std::ostream& operator<<(std::ostream& out, const Utilizator& utilizator) {
    out << "Nume: " << utilizator.getNume() << ", Parola: " << utilizator.getParola()
        << ", Balanta: " << utilizator.getBalanta();
    return out;
}

class Magazin {
private:
    std::vector<JocVideo> jocuriDisponibile;

public:
    [[nodiscard]] const std::vector<JocVideo>& getJocuriDisponibile() const {
        return jocuriDisponibile;
    }

    void adaugaJoc(const JocVideo& joc) {
        jocuriDisponibile.push_back(joc);
    }

    void afiseazaJocuri() const {
        int index = 1;
        for (const auto& joc : jocuriDisponibile) {
            std::cout << index << ". " << joc.getNume() << " - Pret: " << joc.getPret() << std::endl;
            index++;
        }
    }

    [[nodiscard]] const JocVideo& getJoc(int index) const {
        return jocuriDisponibile[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const Magazin& magazin);
};

std::ostream& operator<<(std::ostream& out, const Magazin& magazin) {
    out << "Jocuri Disponibile:\n";
    for (const auto& joc : magazin.getJocuriDisponibile()) {
        out << joc << std::endl;
    }
    return out;
}
class Aplicatie {
private:
    std::vector<Utilizator> utilizatori;
    std::map<std::string, Utilizator> utilizatoriMap;
    Magazin magazin;

    void incarcaUtilizatori() {
        std::ifstream fisierUtilizatori("utilizatori.txt");
        std::string nume, parola;
        double balanta;
        while (fisierUtilizatori >> nume >> parola >> balanta) {
            Utilizator utilizator(nume, parola, balanta);
            utilizatori.push_back(utilizator);
            utilizatoriMap[nume] = utilizator;
        }
        fisierUtilizatori.close();
    }

    void incarcaJocuri() {
        std::ifstream fisierJocuri("jocuri.txt");
        std::string numeJoc;
        double pret;
        while (fisierJocuri >> numeJoc >> pret) {
            JocVideo joc(numeJoc, pret);
            magazin.adaugaJoc(joc);
        }
        fisierJocuri.close();
    }
    static void ascundeParola(std::string &parola) {
        int ch;
        while ((ch = getch()) != '\n' && ch != EOF) {
            if (ch == 13) {
                break;
            }
            std::cout << '*';
            parola.push_back(static_cast<char>(ch));
        }
        std::cout << std::endl;


        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    void logare() {
        std::string numeUtilizator, parolaUtilizator;
        std::cout << "Introduceti numele de utilizator: ";
        std::cin >> numeUtilizator;
        std::cout << "Introduceti parola: ";
        ascundeParola(parolaUtilizator);

        auto it = utilizatoriMap.find(numeUtilizator);
        if (it != utilizatoriMap.end() && it->second.getParola() == parolaUtilizator) {
            std::cout << "Logare cu succes! Bine ati venit, " << numeUtilizator << "!\n";

            while (true) {
                std::cout << "Numele utilizatorului este: " << it->second.getNume() << std::endl;
                std::cout << "1. Vezi toate jocurile disponibile\n";
                std::cout << "2. Cumpara joc\n";
                std::cout << "3. Vezi balanta\n";
                std::cout << "4. Adauga fonduri\n";
                std::cout << "5. Afiseaza jocurile cumparate\n";
                std::cout << "6. Exit\n";
                int optiune;
                std::cin >> optiune;

                if (optiune == 1) {
                    magazin.afiseazaJocuri();
                } else if (optiune == 2) {
                    magazin.afiseazaJocuri();
                    std::cout << "Introduceti numarul jocului pe care doriti sa il cumparati: ";
                    int indexJoc;
                    std::cin >> indexJoc;

                    if (indexJoc >= 1 &&
                        static_cast<std::size_t>(indexJoc) <= magazin.getJocuriDisponibile().size()) {
                        const JocVideo& jocCumparat = magazin.getJoc(indexJoc - 1);
                        double pretJoc = jocCumparat.getPret();
                        if (pretJoc <= it->second.getBalanta()) {
                            it->second.adaugaBani(-pretJoc);
                            it->second.adaugaJocCumparat(jocCumparat);
                            std::cout << "Felicitari! Ati cumparat jocul " << jocCumparat.getNume() << "!\n";
                        } else {
                            std::cout << "Nu aveti suficienti bani pentru a cumpara acest joc.\n";
                        }
                    } else {
                        std::cout << "Optiune invalida.\n";
                    }
                } else if (optiune == 3) {
                    std::cout << "Balanta dumneavoastra: " << it->second.getBalanta() << std::endl;
                    std::cout << "Balanta dumneavoastra: " << it->second.getBalantaFantoma() << std::endl;
                } else if (optiune == 4) {
                    do {
                        std::string input;
                        std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
                        std::getline(std::cin, input);

                        size_t found = input.find(' ');
                        while (found != std::string::npos) {
                            input.erase(found, 1);
                            found = input.find(' ');
                        }

                        try {
                            size_t pos;
                            const double suma = std::stod(input, &pos);

                            if (pos == input.size()) {
                                it->second.adaugaBani(suma);
                                std::cout << "Balanta actualizata cu succes.\n";
                                break;
                            } else {
                                std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
                            }
                        } catch (const std::invalid_argument&) {
                            std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
                        } catch (const std::out_of_range&) {
                            std::cout << "Suma prea mare! Va rugam sa introduceti un numar mai mic.\n";
                        }

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } while (true);
                } else if (optiune == 5) {
                    it->second.afiseazaJocuriCumparate();
                } else if (optiune == 6) {
                    break;
                } else {
                    std::cout << "Optiune invalida.\n";
                    break;
                }
            }
        } else {
            std::cout << "Numele de utilizator sau parola incorecta. Va rugam sa incercati din nou.\n";
        }
    }

    void creareCont() {
        std::string numeUtilizator, parolaUtilizator;

        double balantaNoua = 0.0;

        int numarIncercariMaxim = 3;
        int numarIncercari = 0;

        while (numarIncercari < numarIncercariMaxim) {
            std::string input;
            std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
            std::cin >> input;

            try {
                size_t pos;
                balantaNoua = std::stod(input, &pos);

                if (pos == input.size()) {
                    break;}
                else {
                    std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";}
            } catch (const std::invalid_argument& ) {
                std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
            } catch (const std::out_of_range& ) {
                std::cout << "Suma prea mare! Va rugam sa introduceti un numar mai mic.\n";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            numarIncercari++;
            if (numarIncercari == numarIncercariMaxim) {
                std::cout << "Prea multe încercări nereușite. Iesire din buclă.\n";
                return;
            }
        }

        std::cout << "Introduceti numele de utilizator: ";
        std::cin >> numeUtilizator;
        auto it = utilizatoriMap.find(numeUtilizator);
        if (it == utilizatoriMap.end()) {
            std::cout << "Introduceti parola: ";
            ascundeParola(parolaUtilizator);
            Utilizator utilizatorNou(numeUtilizator, parolaUtilizator, balantaNoua);
            utilizatori.push_back(utilizatorNou);
            utilizatoriMap[numeUtilizator] = utilizatorNou;

            std::ofstream fisierUtilizatoriOut("utilizatori.txt", std::ios_base::app);
            fisierUtilizatoriOut << numeUtilizator << " " << parolaUtilizator << " " << balantaNoua << std::endl;
            fisierUtilizatoriOut.close();

            std::cout << "Cont creat cu succes!\n";
        } else {
            std::cout << "Numele de utilizator este deja folosit. Va rugam sa alegeti alt nume de utilizator!\n";
        }
    }

public:
    Aplicatie() {
        incarcaUtilizatori();
        incarcaJocuri();
    }

    void run() {
        int optiune = 0;
        do {
            std::cout << "1. Logare\n";
            std::cout << "2. Creare cont\n";
            std::cout << "3. Afisare jocuri disponibile\n";
            std::cout << "4. Exit\n";

            if (!(std::cin >> optiune)) {
                std::cout << "Eroare! Introduceti un numar valid.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (optiune) {
                case 1:
                    logare();
                    break;
                case 2:
                    creareCont();
                    break;
                case 3:
                    magazin.afiseazaJocuri();
                    break;
                case 4:
                    std::cout << "La revedere! Multumim ca ati folosit aplicatia noastra!\n";
                    break;
                default:
                    std::cout << "Optiune invalida. Va rugam sa alegeti o optiune valida!\n";
                    break;
            }
        } while (optiune != 4);
    }
};



int main() {
    Aplicatie aplicatie;
    aplicatie.run();

    return 0;
}
