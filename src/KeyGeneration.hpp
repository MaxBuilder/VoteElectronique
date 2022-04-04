#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "CryptoUtils.hpp"

class KeyGeneration {

public:
    static std::tuple<PKey, cpp_int> generate_keys();

};
