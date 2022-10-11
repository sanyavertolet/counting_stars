/**
 * File containing utilities for counting_stars library.
 *
 * @author sanyavertolet
 */
#include "utils.h"

#define ____PROD____

#ifdef ____PROD____
std::filesystem::path project_path() {
    return std::filesystem::current_path();
}

#else
std::filesystem::path project_path() {
    return std::filesystem::current_path().parent_path();
}
#endif //____PROD____

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