#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct PasswordConfig{
    int min_alfabetice;
    int max_alfabetice;
    int min_numerice;
    int max_numerice;
    int min_speciale;
    int max_speciale;
    int total_caractere;
    int nr_separator;
    char separator;
    int nr_parole;
    
};

class PasswordGenerator{
    public:
        virtual ~PasswordGenerator() = default;
        virtual string generate(const PasswordConfig& config) = 0;
};
class LFSRPasswordGenerator : public PasswordGenerator{
    private:
    u_int16_t fct_lfsr(u_int16_t lfsr){
        u_int16_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
        return (lfsr >> 1) | (bit << 15);
    }
    int alege_nr_interval(int lfsr, int min_val, int max_val) const {
        if(min_val == max_val) return min_val;
        return min_val + (lfsr % (max_val - min_val) + 1);
    }
    public:
        string generate(const PasswordConfig& config) override{
        /* u_int16_t lfsr = 0xACE1u; */ // seed initial, aceleasi rezultate constant
        u_int16_t lfsr = static_cast<u_int16_t>(time(nullptr)); //seedul devine ora actuala in secunde, rezultatele difera de fiecare data
        int nr_alfabetice = alege_nr_interval(lfsr, config.min_alfabetice, config.max_alfabetice);
        lfsr = fct_lfsr(lfsr);
        int nr_numerice = alege_nr_interval(lfsr, config.min_numerice, config.max_numerice);
        lfsr = fct_lfsr(lfsr);
        int nr_speciale = config.total_caractere - nr_alfabetice - nr_numerice;
        }
    

};
int main(){

}