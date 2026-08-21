#include <iostream>
#include <memory>
#include <vector>
#include <ctime>
#include "PasswordConfig.h"
#include "LFSRPasswordGenerator.h"
#include "PasswordGenerator.h"

LFSRPasswordGenerator::LFSRPasswordGenerator(){
    lfsr = static_cast<u_int16_t>(time(nullptr));
}
u_int16_t LFSRPasswordGenerator::fct_lfsr(u_int16_t lfsr){
    u_int16_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return (lfsr >> 1) | (bit << 15);
}
int LFSRPasswordGenerator::alege_nr_interval(int lfsr, int min_val, int max_val) const {
    if(min_val == max_val) return min_val;
    return min_val + (lfsr % (max_val - min_val + 1));
}
std::string LFSRPasswordGenerator::generate(const PasswordConfig& config){
    const std::string litere = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string cifre = "0123456789";
    const std::string speciale = "!\"#$%&'()*+,-./:;<=>?@^_`";
    std::string parola = "";
    int nr_alfabetice = 0;
    int nr_numerice = 0;
    int nr_speciale = 0;
    /* u_int16_t lfsr = 0xACE1u; */ // seed initial, aceleasi rezultate constant 
    while(true){
        nr_alfabetice = alege_nr_interval(lfsr, config.min_alfabetice, config.max_alfabetice);
        lfsr = fct_lfsr(lfsr);
        nr_numerice = alege_nr_interval(lfsr, config.min_numerice, config.max_numerice);
        lfsr = fct_lfsr(lfsr);
        nr_speciale = config.total_caractere - nr_alfabetice - nr_numerice;
        if(nr_speciale >= config.min_speciale && nr_speciale <= config.max_speciale){
            break;
            }
            lfsr = fct_lfsr(lfsr);
        }
        for(int i = 0; i < nr_alfabetice; i++){
            lfsr = fct_lfsr(lfsr);
            char ch = static_cast<char>(litere[lfsr % litere.size()]);
            parola += ch;
        }

        for(int i = 0; i < nr_numerice; i++){
            lfsr = fct_lfsr(lfsr);
            char ch = static_cast<char>(cifre[lfsr % cifre.size()]);
            parola += ch;
        }

        for(int i = 0; i < nr_speciale; i++){
            lfsr = fct_lfsr(lfsr);
            char ch = static_cast<char>(speciale[lfsr % speciale.size()]);
            parola += ch;
        }

        for (int i = parola.size() - 1; i > 0; i--){
            lfsr = fct_lfsr(lfsr);
            int j = lfsr % (i + 1);
            char temp = parola[i];
            parola[i] = parola[j];
            parola[j] = temp;
        }
        if(config.nr_separator > 0 && config.separator != '\0'){
            std::string parola_cu_separator = "";
            for(int i=0;i<parola.size();i++){
                parola_cu_separator += parola[i];
                if((i+1) % config.nr_separator == 0 && (i+1) != parola.size()){
                    parola_cu_separator += config.separator;
                }
            }
            parola = parola_cu_separator;
        }
    return parola;       
}
