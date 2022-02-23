#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "CryptoUtils.hpp"

std::tuple<PKey, cpp_int> KeyGeneration();