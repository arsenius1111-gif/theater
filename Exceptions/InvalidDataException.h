#pragma once

#include <stdexcept>
#include <string>

class InvalidDataException : public std::runtime_error
{
public:
    explicit InvalidDataException(const std::string& message)
        : std::runtime_error(message)
    {
    }
};