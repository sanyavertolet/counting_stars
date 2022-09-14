/**
 * Header file that describes DivisionByZeroException.
 *  @author sanyavertolet
 */

#ifndef COUNTING_STARS_DIVISIONBYZEROEXCEPTION_H
#define COUNTING_STARS_DIVISIONBYZEROEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on division by zero.
 *
 * @inherit std::exception
 */
class DivisionByZeroException : std::exception {
private:
    const char* message;

public:
    explicit DivisionByZeroException(const char* msg) : message(msg) {}
    explicit DivisionByZeroException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_DIVISIONBYZEROEXCEPTION_H
