#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(std::string str);
    const char *what() const noexcept override;

private:
    std::string str;
};
