#pragma once

#include <iostream>

//funkcja do uzyskiwania informacji od użytkownika
int getInputFromUser() {
    int input;

    std::cin.clear();
    std::cin >> input;

    return input;
}

//menu dla mst
void mstMenu() {
    int userInput;

    while(true) {
        std::cout << "\nWybierz opcje:\n"
                  << "\t1. Wczytaj dane z pliku\n"
                  << "\t2. Wygeneruj graf losowo\n"
                  << "\t3. Wyswietl graf listowo i macierzowo\n"
                  << "\t4. Algorytm Prima\n"
                  << "\t5. Algorytm Kruskala\n"
                  << "\t0. Zakoncz program" << std::endl;

        userInput = getInputFromUser();

        switch (userInput) {
            case 1:
                std::cout << "Zajebiscie czytam" << std::endl;
                break;
            case 2:
                std::cout << "Generacja masturbacja" << std::endl;
                break;
            case 3:
                std::cout << "Kurwa ale zajebisty graf" << std::endl;
                break;
            case 4:
                std::cout << "Przyszcza" << std::endl;
                break;
            case 5:
                std::cout << "Kluski-Arka" << std::endl;
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}

//menu dla najkrótszej drogi
void shortestPathMenu() {
    int userInput;

    while(true) {
        std::cout << "\nWybierz opcje:\n"
                  << "\t1. Wczytaj dane z pliku\n"
                  << "\t2. Wygeneruj graf losowo\n"
                  << "\t3. Wyswietl graf listowo i macierzowo\n"
                  << "\t4. Algorytm Dijkstry\n"
                  << "\t5. Algorytm Forda-Bellmana\n"
                  << "\t0. Zakoncz program" << std::endl;

        userInput = getInputFromUser();

        switch (userInput) {
            case 1:
                std::cout << "Zajebiscie czytam" << std::endl;
                break;
            case 2:
                std::cout << "Generacja masturbacja" << std::endl;
                break;
            case 3:
                std::cout << "Kurwa ale zajebisty graf" << std::endl;
                break;
            case 4:
                std::cout << "Dick-satra" << std::endl;
                break;
            case 5:
                std::cout << "Cinquecento-Bojman" << std::endl;
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}

//główne menu
void menu() {
    int userInput;

    while(true) {
        std::cout << "\nWybierz problem do testowania:\n"
                  << "\t1. Wyznaczenie minimalnego drzewa rozpinajacego (MST)\n"
                  << "\t2. Wyznaczanie najkrotszej sciezki w grafie\n"
                  << "\t0. Zakoncz testowanie grafu" << std::endl;

        userInput = getInputFromUser();

        switch (userInput) {
            case 1:
                mstMenu();
                break;
            case 2:
                shortestPathMenu();
                break;
            case 0:
                return;

        }
    }
}
