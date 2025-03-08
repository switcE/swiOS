#include "file.h"
#include <fstream>
#include <sstream>

std::string read_file(const std::string &path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        return "Error: Unable to open file.";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
