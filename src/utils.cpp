/**
 * File containing utilities for counting_stars library.
 *
 * @author sanyavertolet
 */
#include "utils.h"

std::filesystem::path project_path() {
    return std::filesystem::current_path().parent_path();
}

std::string get_uncommented_line(std::istream& is) {
    int ch;
    std::string line;
    do {
        ch = is.get();
        if (ch == -1) {
            return "";
        }
        if (ch == '#') {
            getline(is, line);
        }
    }
    while(ch == '#' || isspace(ch));
    getline(is, line);
    return std::string(1, static_cast<char>(ch)) + line;
}