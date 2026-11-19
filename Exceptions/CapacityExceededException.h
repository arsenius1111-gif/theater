#pragma once

#include <stdexcept>
#include <string>

class CapacityExceededException : public std::runtime_error
{
public:
    explicit CapacityExceededException(const std::string& message)
        : std::runtime_error(message)
    {
    }
};