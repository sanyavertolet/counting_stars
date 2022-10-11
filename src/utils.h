/**
 * Header containing utilities for counting_stars library.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_UTILS_H
#define COUNTING_STARS_UTILS_H

#include <iostream>
#include <filesystem>
#include <string>

/**
 * @return path to project root dir
 */
std::filesystem::path project_path();

/**
 * @param is input file stream
 * @return line that contains
 */
std::string get_uncommented_line(std::istream& is);


#endif //COUNTING_STARS_UTILS_H
