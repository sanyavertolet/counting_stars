/**
 * Header file that describes IllegalCapacityException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_ILLEGALCAPACITYEXCEPTION_H
#define COUNTING_STARS_ILLEGALCAPACITYEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on operations between two matrices that doesn't have matching capacities.
 *
 * @inherit std::exception
 */
class IllegalCapacityException : std::exception {
private:
    const char* message;
    static const std::string default_message;
public:
    IllegalCapacityException() : message(default_message.c_str()) {}
    explicit IllegalCapacityException(const char* msg) : message(msg) {}
    explicit IllegalCapacityException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message;
    }
    explicit IllegalCapacityException(const std::string& lhs, const std::string & rhs) {
        message = (default_message + ": [" + lhs + "] and [" + rhs + "].").c_str();
    }
};

#endif //COUNTING_STARS_ILLEGALCAPACITYEXCEPTION_H
