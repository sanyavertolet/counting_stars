/**
 * Header file that describes OutOfRangeException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_OUTOFRANGEEXCEPTION_H
#define COUNTING_STARS_OUTOFRANGEEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on attempt to access data that does not exist.
 *
 * @inherit std::exception
 */
class OutOfRangeException : std::exception {
private:
    const char* message;
public:
    OutOfRangeException() : message("Could not cast properly.") {}
    explicit OutOfRangeException(const char* msg) : message(msg) {}
    explicit OutOfRangeException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_OUTOFRANGEEXCEPTION_H
