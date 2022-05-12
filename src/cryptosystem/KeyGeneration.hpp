#ifndef __KEY_GENERATION_H
#define __KEY_GENERATION_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "CryptoUtils.hpp"
#include "../Properties.hpp"

namespace mp = boost::multiprecision;

class KeyGeneration
{

public:
    static std::tuple<PKey, mp::cpp_int> generate_keys();
};

#endif // __KEY_GENERATION_H
