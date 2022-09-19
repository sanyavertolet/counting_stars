/**
 * Header file that describes CastException.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_CASTEXCEPTION_H
#define COUNTING_STARS_CASTEXCEPTION_H

#include <exception>
#include <string>

/**
 * Exception thrown on incorrect cast.
 *
 * @inherit std::exception
 */
class CastException : std::exception {
private:
    const char* message;

public:
    CastException() : message("Could not cast properly.") {}
    explicit CastException(const char* msg) : message(msg) {}
    explicit CastException(const std::string& msg) : message(msg.c_str()) {}
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return message;
    }
};

#endif //COUNTING_STARS_CASTEXCEPTION_H
