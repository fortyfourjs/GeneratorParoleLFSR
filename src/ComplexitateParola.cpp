#include "ComplexitateParola.h"

StrengthLevel PasswordValidator::evaluateStrength(const std::string& password) {
    if (password.length() < 8) {
        return StrengthLevel::Slab;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char ch : password) {
        if (std::isupper(ch)) hasUpper = true;
        else if (std::islower(ch)) hasLower = true;
        else if (std::isdigit(ch)) hasDigit = true;
        else hasSpecial = true;
    }

    int score = hasUpper + hasLower + hasDigit + hasSpecial;

    if (password.length() >= 12 && score >= 3) {
        return StrengthLevel::Puternic;
    } else if (password.length() >= 8 && score >= 2) {
        return StrengthLevel::Mediu;
    }

    return StrengthLevel::Slab;
}

std::string PasswordValidator::strengthToString(StrengthLevel strength) {
    switch (strength) {
        case StrengthLevel::Slab: return "Slaba";
        case StrengthLevel::Mediu: return "Medie";
        case StrengthLevel::Puternic: return "Puternica";
    }
    return "Necunoscut";
}