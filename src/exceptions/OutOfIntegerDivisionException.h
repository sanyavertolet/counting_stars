/**
 * Header file that describes out of integer division exception.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_OUTOFINTEGERDIVISION_H
#define COUNTING_STARS_OUTOFINTEGERDIVISION_H

#include <exception>
#include <string>

/**
 * Exception is thrown when cannot divide two StringInts as integers.
 *
 * @inherit std::exception
 */
class OutOfIntegerDivisionException : std::exception {
private:
    const char* message;
public:
    explicit OutOfIntegerDivisionException(const char* msg) : message(msg) {}
    explicit OutOfIntegerDivisionException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_OUTOFINTEGERDIVISION_H
