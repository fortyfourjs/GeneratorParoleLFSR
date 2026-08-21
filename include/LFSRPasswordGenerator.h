#pragma once
#include "PasswordGenerator.h"
#include <string>


class LFSRPasswordGenerator : public PasswordGenerator{
    private:
        u_int16_t lfsr;

        u_int16_t fct_lfsr(u_int16_t lfsr);
    int alege_nr_interval(int lfsr, int min_val, int max_val) const;
    public:
        LFSRPasswordGenerator();
        ~LFSRPasswordGenerator() override = default;
        std::string generate(const PasswordConfig& config) override;
};