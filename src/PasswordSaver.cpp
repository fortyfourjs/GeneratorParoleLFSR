#include "PasswordSaver.h"
#include <fstream>


bool PasswordSaver::saveFile(const std::string& filename, const std::string& password){
    std::ofstream file(filename, std::ios::app);
    if(!file.is_open()){
        return false;
    }
    file << password << '\n';
    return true;
}