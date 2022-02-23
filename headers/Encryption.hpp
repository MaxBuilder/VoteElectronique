#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include "CryptoUtils.hpp"

using namespace boost::multiprecision;

cpp_int Encrypt(PKey PK);