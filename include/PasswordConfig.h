#pragma once

struct PasswordConfig{
    int min_alfabetice;
    int max_alfabetice;
    int min_numerice;
    int max_numerice;
    int min_speciale;
    int max_speciale;
    int total_caractere;
    int nr_separator;
    int nr_parole;
    char separator;
    
    bool ValidareParola() const{
        int suma = min_alfabetice + min_numerice + min_speciale;
        return (total_caractere >= 6 && suma <= total_caractere);
    }
};