#ifndef ENCRYPT_STRATEGY_H
#define ENCRYPT_STRATEGY_H

#include <string>

class BaseEncryptStrategy {
public:
    virtual std::string encrypt(const std::string &input) = 0;
};

#endif // ENCRYPT_STRATEGY_H
