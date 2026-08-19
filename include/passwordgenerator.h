#pragma once


class PasswordGenerator{
    public:
        virtual ~PasswordGenerator() = default;
        virtual string generate(const PasswordConfig& config) = 0;
};