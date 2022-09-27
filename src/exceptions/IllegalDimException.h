/**
 * Header file that describes IllegalDimException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_ILLEGALDIMEXCEPTION_H
#define COUNTING_STARS_ILLEGALDIMEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on operations between two matrices that doesn't have matching dimensions.
 *
 * @inherit std::exception
 */
class IllegalDimException : std::exception {
private:
    const char* message;
    static const std::string default_message;
public:
    IllegalDimException() : message("Matrices dimensions doesn't match") {}
    explicit IllegalDimException(const char* msg) : message(msg) {}
    explicit IllegalDimException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
    explicit IllegalDimException(const std::string& lhs, const std::string & rhs) {
        message = (default_message + ": [" + lhs + "] and [" + rhs + "].").c_str();
    }
};

#endif //COUNTING_STARS_ILLEGALDIMEXCEPTION_H
