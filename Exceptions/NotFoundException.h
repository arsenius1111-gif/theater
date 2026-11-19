#pragma once

#include <stdexcept>

class NotFoundException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};