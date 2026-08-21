#include <iostream>
#include <memory>
#include <string>
#include "LFSRPasswordGenerator.h"
#include "PasswordConfig.h"
#include "PasswordSaver.h"


int main(){
    PasswordConfig config;
    std::cout << "min alfabetice" << '\n';
    std::cin >> config.min_alfabetice;
    std::cout << "max alfabetice" << '\n';
    std::cin >> config.max_alfabetice;
    std::cout << "min numerice" << '\n';
    std::cin >> config.min_numerice;
    std::cout << "max numerice" << '\n';
    std::cin >> config.max_numerice;
    std::cout << "min speciale" << '\n';
    std::cin >> config.min_speciale;
    std::cout << "max speciale" << '\n';
    std::cin >> config.max_speciale;
    std::cout << "total caractere" << '\n';
    std::cin >> config.total_caractere;
    std::cout << "interval separator" << '\n';
    std::cin >> config.nr_separator;
    config.separator = '-';

    std::unique_ptr<PasswordGenerator> generator = std::make_unique<LFSRPasswordGenerator>();
    for(int i=0;i<100;i++){
        std::string parola = generator->generate(config);
        std::cout << "Parola nr(" << i << "): " << parola << '\n';
        PasswordSaver::saveFile("Parole.txt", parola);
    }
    return 0;
}