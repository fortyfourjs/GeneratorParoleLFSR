#include <iostream>
#include <memory>
#include <string>
#include "LFSRPasswordGenerator.h"
#include "PasswordConfig.h"
#include "PasswordSaver.h"
#include "CitireInput.h"
#include "ComplexitateParola.h"


int main(){
    PasswordConfig config;
    while(true){
        config.min_alfabetice = CitireInput::citesteNumarPozitiv("Minim caractere alfabetice: ");
        config.max_alfabetice = CitireInput::citesteNumarPozitiv("Maxim caractere alfabetice: ");
        config.min_numerice = CitireInput::citesteNumarPozitiv("Minim caractere numerice: ");
        config.max_numerice = CitireInput::citesteNumarPozitiv("Maxim caractere numerice: ");
        config.min_speciale = CitireInput::citesteNumarPozitiv("Minim caractere speciale: ");
        config.max_speciale = CitireInput::citesteNumarPozitiv("Maxim caractere speciale: ");
        config.total_caractere = CitireInput::citesteNumarPozitiv("Total caractere: ");
        config.nr_separator = CitireInput::citesteNumarPozitiv("Interval separator: ");
        config.separator = '-';
        if(config.ValidareParola()){
            std::cout << "\nConfiguratie valida!";
            break;
        }
        std::cout << "\nEROARE: Suma minimelor depaseste totalul caracterelor sau totalul < 6\n";
        std::cout << "Reintroduceti datele\n";
    }

    std::unique_ptr<PasswordGenerator> generator = std::make_unique<LFSRPasswordGenerator>();
    for(int i=0;i<100;i++){
        std::string parola = generator->generate(config);
        std::cout << "Parola nr(" << i << "): " << parola << '\n';
        StrengthLevel nivel = PasswordValidator::evaluateStrength(parola);
        std::cout << "Complexitate: " << PasswordValidator::strengthToString(nivel) << '\n';
        PasswordSaver::saveFile("Parole.txt", parola);
    }
    return 0;
}