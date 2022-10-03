/**
 * Header file that describes parse exception.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_PARSEEXCEPTION_H
#define COUNTING_STARS_PARSEEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on incorrect parsing of entities described in this library.
 *
 * @inherit std::exception
 */
class ParseException : std::exception {
private:
    const char* message;
public:
    explicit ParseException(const char* msg) : message(msg) {}
    explicit ParseException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_PARSEEXCEPTION_H
