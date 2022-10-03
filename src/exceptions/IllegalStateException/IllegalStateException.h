/**
 * Header file that describes IllegalDigitException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_ILLEGALSTATEEXCEPTION_H
#define COUNTING_STARS_ILLEGALSTATEEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on illegal state of an object.
 *
 * @inherit std::exception
 */
class IllegalStateException : std::exception {
private:
    const char* message;

public:
    explicit IllegalStateException(const char* msg) : message(msg) {}
    explicit IllegalStateException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_ILLEGALSTATEEXCEPTION_H
