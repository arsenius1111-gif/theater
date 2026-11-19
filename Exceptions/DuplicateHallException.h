#pragma once

#include <stdexcept>
#include <string>

class DuplicateHallException : public std::runtime_error
{
public:
    explicit DuplicateHallException(const std::string& message)
        : std::runtime_error(message)
    {
    }
};