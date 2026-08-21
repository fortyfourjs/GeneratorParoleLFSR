#pragma once
#include <string>

class PasswordSaver{
    public:
       static bool saveFile(const std::string& filename, const std::string& password);

};