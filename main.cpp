#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <limits>
//#include <algorithm>
// :)
class Utilizator {
private:
    std::string nume;
    std::string parola;
    double balanta;

public:
    Utilizator() : nume(), parola(), balanta(0.0) {}
    Utilizator( std::string& nume, std::string& parola, double balanta)
            : nume(nume), parola(parola), balanta(balanta) {}
    Utilizator(const Utilizator& other) = default;
    ~Utilizator() = default;

    [[nodiscard]] const std::string& getNume() const  {
        return nume;
    }

    [[nodiscard]] const std::string& getParola() const {
        return parola;
    }

    [[nodiscard]] double getBalanta() const {
        return balanta;
    }

    void adaugaBani(double suma) {
        balanta += suma;
    }
};

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

    [[nodiscard]]double getPret() const {
        return pret;
    }
};

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
};

int main() {
    std::vector<Utilizator> utilizatori;
    std::map<std::string, Utilizator> utilizatoriMap;
    std::ifstream fisierUtilizatoriIn("utilizatori.txt");
    std::ofstream fisierUtilizatoriOut("utilizatori.txt", std::ios_base::app);



    std::ifstream fisierUtilizatori("utilizatori.txt");
    std::string nume, parola;
    double balanta;
    while (fisierUtilizatori >> nume >> parola >> balanta) {
        Utilizator utilizator(nume, parola, balanta);
        utilizatori.push_back(utilizator);
        utilizatoriMap[nume] = utilizator;
    }
    fisierUtilizatori.close();

    std::ifstream fisierJocuri("jocuri.txt");
    Magazin magazin;
    std::string numeJoc;
    double pret;
    while (fisierJocuri >> numeJoc >> pret) {
        JocVideo joc(numeJoc, pret);
        magazin.adaugaJoc(joc);
    }
    fisierJocuri.close();

    while (true) {
        std::cout << "1. Logare\n";
        std::cout << "2. Creare cont\n";
        std::cout << "3. Exit\n";

        std::string optiuneStr;
        std::getline(std::cin, optiuneStr);

        int optiune;
        std::istringstream ss(optiuneStr);
        if (ss >> optiune) {
            if (optiune >= 1 && optiune <= 3) {

                if (optiune == 1) {
                    std::string numeUtilizator, parolaUtilizator;
                    std::cout << "Introduceti numele de utilizator: ";
                    std::cin >> numeUtilizator;
                    std::cout << "Introduceti parola: ";
                    std::cin >> parolaUtilizator;

                    auto it = utilizatoriMap.find(numeUtilizator);
                    if (it != utilizatoriMap.end() && it->second.getParola() == parolaUtilizator) {
                        std::cout << "Logare cu succes! Bine ati venit, " << numeUtilizator << "!\n";

                        while (true) {
                            std::cout << "Numele utilizatorului este: " << it->second.getNume() << std::endl;
                            std::cout << "1. Vezi toate jocurile disponibile\n";
                            std::cout << "2. Cumpara joc\n";
                            std::cout << "3. Vezi balanta\n";
                            std::cout << "4. Adauga fonduri\n";
                            std::cout << "5. Exit\n";
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
                                    const JocVideo &jocCumparat = magazin.getJoc(indexJoc - 1);
                                    double pretJoc = jocCumparat.getPret();
                                    if (pretJoc <= it->second.getBalanta()) {
                                        it->second.adaugaBani(-pretJoc);
                                        std::cout << "Felicitari! Ati cumparat jocul " << jocCumparat.getNume()
                                                  << "!\n";
                                    } else {
                                        std::cout << "Nu aveti suficienti bani pentru a cumpara acest joc.\n";
                                    }
                                } else {
                                    std::cout << "Optiune invalida.\n";
                                }
                            } else if (optiune == 3) {
                                std::cout << "Balanta dumneavoastra: " << it->second.getBalanta() << std::endl;
                            } else if (optiune == 4) {
                                std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
                                bool sumaValida = false;
                                double suma;
                                std::cin >> suma;

                                while (!sumaValida) {
                                    std::string input;
                                    std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
                                    std::cin >> input;

                                    try {
                                        size_t pos;
                                        suma = std::stod(input, &pos);

                                        if (pos == input.size()) {
                                            // Verificam dacă toate caracterele din input sunt convertite la numar
                                            sumaValida = true;
                                        } else {
                                            std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
                                        }
                                    } catch (const std::invalid_argument& e) {
                                        std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
                                    } catch (const std::out_of_range& e) {
                                        std::cout << "Suma prea mare! Va rugam sa introduceti un numar mai mic.\n";
                                    }

                                    // Curatam buffer ul de intrare pentru a evita bucle nedorite
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }



                                it->second.adaugaBani(suma);
                                std::cout << "Balanta actualizata cu succes.\n";
                            } else if (optiune == 5) {
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
            } else {
                std::cout << "Optiune invalida. Va rugam sa alegeti o optiune valida!\n";
            }
        }     if (optiune == 2) {
            std::string numeUtilizator, parolaUtilizator;
            double balantaNoua;

            bool balantaValida = false;

            while (!balantaValida) {
                std::string input;
                std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
                std::cin >> input;

                try {
                    size_t pos;
                    balanta = std::stod(input, &pos);

                    if (pos == input.size()) {
                        balantaValida = true;
                    } else {
                        std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
                    }
                } catch (const std::invalid_argument& e) {
                    std::cout << "Suma invalida! Va rugam sa introduceti un numar real.\n";
                } catch (const std::out_of_range& e) {
                    std::cout << "Suma prea mare! Va rugam sa introduceti un numar mai mic.\n";
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "Introduceti numele de utilizator: ";
            std::cin >> numeUtilizator;
            auto it = utilizatoriMap.find(numeUtilizator);
            if (it == utilizatoriMap.end()) {
                std::cout << "Introduceti parola: ";
                std::cin >> parolaUtilizator;
                std::cout << "Introduceti balanta initiala: ";
                std::cin >> balantaNoua;
                Utilizator utilizatorNou(numeUtilizator, parolaUtilizator, balantaNoua);
                utilizatori.push_back(utilizatorNou);
                utilizatoriMap[numeUtilizator] = utilizatorNou;
                fisierUtilizatoriOut.open("utilizatori.txt", std::ios_base::app);
                fisierUtilizatoriOut << numeUtilizator << " " << parolaUtilizator << " " << balantaNoua << std::endl;
                fisierUtilizatoriOut.close();
                std::cout << "Cont creat cu succes!\n";
                std::cout << "Numele utilizatorului este: " << it->second.getNume() << std::endl;
            } else {
                std::cout << "Numele de utilizator este deja folosit. Va rugam sa alegeti alt nume de utilizator!\n";
            }
        } else if (optiune == 3) {
            std::cout << "La revedere! Multumim ca ati folosit aplicatia noastra!\n";
            break;
        } else {
            std::cout << "Optiune invalida. Va rugam sa alegeti o optiune valida!\n";
        }
    }
    fisierUtilizatoriIn.close();
    fisierUtilizatoriOut.close();
    return 0;
}