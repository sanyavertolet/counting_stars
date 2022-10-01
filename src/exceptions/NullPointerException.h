/**
 * Header file that describes NullPointerException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_NULLPOINTEREXCEPTION_H
#define COUNTING_STARS_NULLPOINTEREXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on null pointer access.
 *
 * @inherit std::exception
 */
class NullPointerException : std::exception {
private:
    const char* message;
    static const std::string default_message;
public:
    NullPointerException() : message(default_message.c_str()) {}
    explicit NullPointerException(const char* msg) {
        message = (default_message + ": " + std::string(msg)).c_str();
    }
    explicit NullPointerException(const std::string& msg) {
        message = (default_message + ": " + msg).c_str();
    }
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_NULLPOINTEREXCEPTION_H
