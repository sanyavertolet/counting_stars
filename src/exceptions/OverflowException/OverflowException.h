/**
 * Header file that describes overflow exception.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_OVERFLOWEXCEPTION_H
#define COUNTING_STARS_OVERFLOWEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on attempt to put too big number into a smaller one implicitly.
 *
 * @inherit std::exception
 */
class OverflowException : std::exception {
private:
    const char* message;
public:
    explicit OverflowException(const char* msg) : message(msg) {}
    explicit OverflowException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message;
    }
};

#endif //COUNTING_STARS_OVERFLOWEXCEPTION_H
