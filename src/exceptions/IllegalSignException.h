/**
 * Header file that describes IllegalSignException.
 *  @author sanyavertolet
 */

#ifndef COUNTING_STARS_ILLEGALSIGNEXCEPTION_H
#define COUNTING_STARS_ILLEGALSIGNEXCEPTION_H

#include <exception>

/**
 * Exception thrown on illegal sign of a number.
 *
 * @inherit std::exception
 */
class IllegalSignException : std::exception {
private:
    const char* message;

public:
    explicit IllegalSignException(const char* msg) : message(msg) {}
    explicit IllegalSignException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_ILLEGALSIGNEXCEPTION_H
