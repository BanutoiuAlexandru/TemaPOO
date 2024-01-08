#include "Aplicatie.hpp"
#include "JocRPG.hpp"
#include <fstream>
#include <limits>
#include <iostream>

Aplicatie::Aplicatie() {
    incarcaUtilizatori();
    incarcaJocuri();
}

void Aplicatie::incarcaUtilizatori() {
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

/*void Aplicatie::incarcaJocuri() {

    std::ifstream fisierJocuri("jocuri.txt");
    std::string numeJoc;
    double pret;
    std::string tipJoc;
    while (fisierJocuri >> numeJoc >> pret >> tipJoc) {
        JocVideo* joc = nullptr;
        if (tipJoc == "RPG") {
            joc = new JocRPG(numeJoc, pret);
        } else {
            joc = new JocVideo(numeJoc, pret);
        }

        magazin.adaugaJoc(joc);
    }
    fisierJocuri.close();
}
*/
void Aplicatie::logare() {
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
                    const JocVideo* jocCumparat = magazin.getJoc(indexJoc - 1);
                    double pretJoc = jocCumparat->getPret();
                    if (pretJoc <= it->second.getBalanta()) {
                        it->second.adaugaBani(-pretJoc);
                        it->second.adaugaJocCumparat(*jocCumparat);
                        std::cout << "Felicitari! Ati cumparat jocul " << jocCumparat->getNume() << "!\n";
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
            }
        }
    } else {
        std::cout << "Numele de utilizator sau parola incorecta. Va rugam sa incercati din nou.\n";
    }
}

void Aplicatie::creareCont() {
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
        std::cin >> parolaUtilizator;
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

void Aplicatie::run() {
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

void Aplicatie::incarcaJocuri() {

}
