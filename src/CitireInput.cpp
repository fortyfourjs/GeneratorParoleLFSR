#include <iostream>
#include "CitireInput.h"
#include <limits>

int CitireInput::citesteNumarPozitiv(const std::string& mesaj){
    int valoare;
    while(true){
        std::cout << mesaj;
        if(std::cin >> valoare && valoare >= 0){
            return valoare;
        }
        std::cout << "EROARE: Introduceti un numar valid!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}