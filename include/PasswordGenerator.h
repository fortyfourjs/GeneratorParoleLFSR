#pragma once
#include <string>
#include "PasswordConfig.h"


class PasswordGenerator{
    public:
        virtual ~PasswordGenerator() = default;
        virtual std::string generate(const PasswordConfig& config) = 0;
};