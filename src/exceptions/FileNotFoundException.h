/**
 * Header file that describes FileNotFoundException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_FILENOTFOUNDEXCEPTION_H
#define COUNTING_STARS_FILENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on missing file.
 *
 * @inherit std::exception
 */
class FileNotFoundException : std::exception {
private:
    const char* message;
    static const std::string default_message;
public:
    FileNotFoundException() : message(default_message.c_str()) {}
    explicit FileNotFoundException(const char* file_path) {
        message = (default_message + ": " + std::string(file_path)).c_str();
    }
    explicit FileNotFoundException(const std::string& file_path) {
        message = (default_message + ": " + file_path).c_str();
    }
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

std::string const FileNotFoundException::default_message = "File not found";

#endif //COUNTING_STARS_FILENOTFOUNDEXCEPTION_H
