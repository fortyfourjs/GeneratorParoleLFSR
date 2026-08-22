#pragma once

#include <string>

enum class StrengthLevel {
    Slab,
    Mediu,
    Puternic
};

class PasswordValidator {
public:
    static StrengthLevel evaluateStrength(const std::string& password);
    static std::string strengthToString(StrengthLevel strength);
};