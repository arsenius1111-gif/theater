#pragma once

#include <stdexcept>
#include <string>

class OutOfRangeException : public std::runtime_error
{
public:
    explicit OutOfRangeException(const std::string& message)
        : std::runtime_error(message)
    {
    }
};