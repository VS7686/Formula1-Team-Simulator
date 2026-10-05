#pragma once

#include <stdexcept>
#include <string>

#include "Money.h"

namespace f1 {

// Base class for every game-specific error.
class GameException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InsufficientFundsException : public GameException {
public:
    InsufficientFundsException(const Money& needed, const Money& available)
        : GameException("Insufficient funds: need " + needed.str() + ", have " + available.str()) {}
};

class ContractException : public GameException {
public:
    using GameException::GameException;
};

class InvalidStateException : public GameException {
public:
    using GameException::GameException;
};

}  // namespace f1
